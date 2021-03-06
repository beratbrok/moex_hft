using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Xml;
using Mono.Options;
using System.Collections;

namespace prebuild {
	public enum GeneratorMode { 
		Asts,
		Spectra
	}
	class FastTemplatesCodeGenerator {
		List<string> Strings { get { return CurrentFile.Lines; } }

		public bool WriteConstantCheckingCode { get; set; }

		public string RobotCpp { get; set; }
		public string ManagerSourceFileH { get; set; }
		public string ManagerSourceFileCpp { get; set; }
		public string SourceTypes { get; set; }
		public string AstsServerConfigFileName { get; set; }
		public string FortsServerConfigFileName { get; set; }
		public string AstsTemplateFile { get; set; }
		public string SpectraTemplateFile { get; set; }

		protected TextFile RobotCppFile { get; set; }
		protected TextFile ManagerHFile { get; set; }
		protected TextFile ManagerCppFile { get; set; }
		protected TextFile TypesFile { get; set; }
		protected TextFile CurrentFile { get; set; }

		void WriteLine (string line) { 
			if(CurrentFile == null)
				CurrentFile = ManagerHFile;
			CurrentFile.Add(line);
		}

		protected XmlNode TemplatesNode { get; private set; }
		protected string Prefix { get; private set; }
		protected GeneratorMode Mode { get; private set; }

		string ConstStr(string str) {
			return "\"" + str + "\"";
		}
		string NodeValue(XmlNode node) {
			if(node.ChildNodes.Count == 0 || node.ChildNodes[0].Value == null)
				return "";
			return node.ChildNodes[0].Value.ToString();
		}
		XmlNode FindNode(XmlNodeList list, string name) {
			foreach(XmlNode node in list) {
				if(node.Name == name)
					return node;
			}
			return null;
		} 
		List<XmlNode> GetMarketDataGroups(XmlNode config) {
			List<XmlNode> list = new List<XmlNode>();
			foreach(XmlNode node in config) {
				if(node.NodeType == XmlNodeType.Comment)
					continue;
				if(node.Name != "MarketDataGroup")
					continue;
				list.Add(node);
			}
			return list;
		}
		bool GenerateAddChannelsCode_FORTS() { 
			Console.WriteLine("generate add forts channels code...");

			XmlDocument doc = new XmlDocument();
			doc.Load(FortsServerConfigFileName);

			ClearRegion(AddDefaultChannels_GeneratedCode);
			SetPosition(AddDefaultChannels_GeneratedCode);

			XmlNode config = FindNode(doc.ChildNodes, "configuration");
			if(config == null)
				throw new ArgumentException("configuration node not found in " + FortsServerConfigFileName);

			WriteLine("\tif(this->AllowFortsMarket()) {");
			WriteLine("\t\tFortsFeedChannel *channel = new FortsFeedChannel();");
			List<XmlNode> mdgList = GetMarketDataGroups(config);
			foreach(XmlNode node in mdgList) {
				GenerateMarketDataGroupCode(node);
			}
			WriteLine("\t\tthis->m_fortsChannel = channel;");
			WriteLine("\t}");
			return true;
		}
		string GetMarketDataGroupId(string value) {
			string[] list = value.Split('-');
			string res = "mdgid";
			for(int i = 0; i < list.Length; i++) {
				if(list[i].Length == 1)
					list[i] = list[i].ToUpper();
				else 
					list[i] = list[i].Substring(0, 1).ToUpper() + list[i].Substring(1).ToLower();
				res += list[i];
			}
			return res;
		}
		string GetMarketDataGroupName(string value) {
			string[] list = value.Split('-');
			string res = "";
			for(int i = 0; i < list.Length; i++) {
				if(list[i].Length == 1)
					list[i] = list[i].ToUpper();
				else 
					list[i] = list[i].Substring(0, 1).ToUpper() + list[i].Substring(1).ToLower();
				res += list[i];
			}
			return res;
		}
		class FortsConnection { 
			public FortsConnection(XmlNode node) {
				Node = node;
				Type = FindField("type");
				Protocol = FindField("protocol");
				SrcIp = FindField("src-ip");
				Ip = FindField("ip");
				Port = FindField("port");
				Feed = FindField("feed");
			}
			public XmlNode Node { get; set; }
			public string Type { get; set; } 
			public string TypeString { get { return "\"" + Type + "\""; } }
			public string Protocol { get; set; }
			public string ProtocolString { get { return "FeedConnectionProtocol::" + Protocol.Replace('/', '_'); }  }
			public string SrcIp { get; set; }
			public string SrcIpString { get { return "\"" + SrcIp + "\""; } }
			public string Ip { get; set; }
			public string IpString { get { return "\"" + Ip + "\""; } }
			public string Port { get; set; }
			public string Feed { get; set; }

			public bool IsIncremental { get { return Type == "Incremental"; } }
			public bool IsInstrumentIncremental { get { return Type == "Instrument Incremental"; } }
			public bool IsInstrumentSnapshot { get { return Type == "Instrument Replay"; } }
			public bool IsSnapshot { get { return Type == "Snapshot"; } }
			public bool IsHistoricalReplay { get { return Type == "HistoricalReplay"; } }
			public bool IsUdp { get { return Protocol == "UDP/IP"; } }

			string FindField(string name) {
				foreach(XmlNode node in Node.ChildNodes) {
					if(node.Name == name)
						return node.ChildNodes[0].Value.ToString();
				}
				return string.Empty;
			}
		}
		List<FortsConnection> GetFortsConnections(XmlNode node) {
			List<FortsConnection> list = new List<FortsConnection>();
			foreach(XmlNode child in node.ChildNodes[0].ChildNodes) {
				if(child.NodeType == XmlNodeType.Comment)
					continue;
				if(child.Name != "connection")
					throw new Exception("forts connection!");
				list.Add(new FortsConnection(child));
			}
			return list;
		}
		void GenerateMarketDataGroupCode(XmlNode node) {
			string fid = node.Attributes["feedType"].Value;
			string feedType = GetMarketDataGroupId(fid);
			string feedName = GetMarketDataGroupName(fid);
			string md = HasAttribute(node, "marketDepth")? node.Attributes["marketDepth"].Value: "0";
			string mid = node.Attributes["marketID"].Value;
			string label = node.Attributes["label"].Value;

			WriteLine("\t\tif(this->AllowMarketDataGroup(MarketDataGroupId::" + feedType + ")) {");
			WriteLine("\t\t\tFortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::" + feedType + ", \"" + mid + "\", " + md + ", \"" + label + "\");");
			List<FortsConnection> conn = GetFortsConnections(node);

			List<FortsConnection> inc = conn.FindAll((c) => c.IsIncremental );
			List<FortsConnection> snap = conn.FindAll((c) => c.IsSnapshot);
			List<FortsConnection> instrInc = conn.FindAll((c) => c.IsInstrumentIncremental);
			List<FortsConnection> instrSnap = conn.FindAll((c) => c.IsInstrumentSnapshot);
			FortsConnection hr = conn.FirstOrDefault((c) => c.IsHistoricalReplay);

			string feedConnectionName = "FeedConnection_FORTS_INC";
			if(fid.Contains("BOOK")) 
				feedConnectionName = "FeedConnection_FORTS_OBR";
			else if(fid.Contains("TRADES"))
				feedConnectionName = "FeedConnection_FORTS_TLR";
			else if(fid.Contains("INDEX"))
				feedConnectionName = "FeedConnection_FORTS_INDEX";
			else if(fid.Contains("NEWS-SKRIN"))
				feedConnectionName = "FeedConnection_FORTS_NEWS_SKRIN";
			else if(fid.Contains("NEWS"))
				feedConnectionName = "FeedConnection_FORTS_NEWS";
			else 
				feedConnectionName = "FeedConnection_FORTS_INC";
			
			if(inc != null && inc.Count == 2) {
				WriteLine("\t\t\tgroup->Inc( new " + feedConnectionName + "(" + 
					"\"" + fid + " Inc\", " +
					"\"" + label + " Incremental\", " + 
					"'" + mid + "', " + 
					inc[0].ProtocolString + ", " +
					inc[0].SrcIpString + ", " + 
					inc[0].IpString + ", " + 
					inc[0].Port + ", " + 
					inc[1].SrcIpString + ", " + 
					inc[1].IpString + ", " + 
					inc[1].Port +
					") );");
			}

			if(snap != null && snap.Count == 2) {
				WriteLine("\t\t\tgroup->Snap( new FeedConnection_FORTS_SNAP(" + 
					"\"" + fid + " Snap\", " +
					"\"" + label + " Snapshot\", " + 
					"'" + mid + "', " + 
					snap[0].ProtocolString + ", " +
					snap[0].SrcIpString + ", " + 
					snap[0].IpString + ", " + 
					snap[0].Port + ", " + 
					snap[1].SrcIpString + ", " + 
					snap[1].IpString + ", " + 
					snap[1].Port +
					") );");
			}

			if(hr != null) {
				WriteLine("\t\t\tgroup->Hr( new FeedConnection_FORTS_HR(" + 
					"\"" + fid + " Hr\", " +
					"\"" + label + "\", " + 
					"'" + mid + "', " + 
					hr.ProtocolString + ", " +
					"0" + ", " + 
					hr.IpString + ", " + 
					hr.Port + ", " + 
					"0" + ", " + 
					"0" + ", " + 
					"0" +
					") );");
			}

			if(instrInc != null && instrInc.Count == 2) {
				WriteLine("\t\t\tgroup->InstrInc( new FeedConnection_FORTS_INSTR_INC(" + 
					"\"" + fid + " Instrument Incremetnal\", " +
					"\"" + label + "\", " + 
					"'" + mid + "', " + 
					instrInc[0].ProtocolString + ", " +
					instrInc[0].SrcIpString + ", " + 
					instrInc[0].IpString + ", " + 
					instrInc[0].Port + ", " + 
					instrInc[1].SrcIpString + ", " + 
					instrInc[1].IpString + ", " + 
					instrInc[1].Port +
					") );");
			}

			if(instrSnap != null && instrSnap.Count == 2) {
				WriteLine("\t\t\tgroup->InstrReplay( new FeedConnection_FORTS_INSTR_SNAP(" + 
					"\"" + fid + " Instrument Replay\", " +
					"\"" + label + "\", " + 
					"'" + mid + "', " + 
					instrSnap[0].ProtocolString + ", " +
					instrSnap[0].SrcIpString + ", " + 
					instrSnap[0].IpString + ", " + 
					instrSnap[0].Port + ", " + 
					instrSnap[1].SrcIpString + ", " + 
					instrSnap[1].IpString + ", " + 
					instrSnap[1].Port +
					") );");
			}
			WriteLine("\t\t\tchannel->" + feedName + "(group);");
			WriteLine("\t\t}");
		}
		bool GenerateAddChannelsCode_ASTS() {
			Console.WriteLine("generate add asts channels code...");

			XmlDocument doc = new XmlDocument();
			doc.Load(AstsServerConfigFileName);

			ClearRegion(AddDefaultChannels_GeneratedCode);
			SetPosition(AddDefaultChannels_GeneratedCode);
			XmlNode parent = null;
			foreach(XmlNode nd in doc.ChildNodes) {
				if(nd.Name == "configuration") {
					parent = nd;
					break;
				}
			}

			foreach(XmlNode node in parent.ChildNodes) {
				string channelName = node.Attributes["id"].Value;
				string channelLabel = node.Attributes["label"].Value;
				string channelNameUpper = channelName.Substring(0, 1).ToUpper() + channelName.Substring(1).ToLower();

				WriteLine("\tif(this->Allow" + channelNameUpper + "Market()) {");
				WriteLine("\t\tAstsFeedChannel *" + channelName.ToLower() + " = new AstsFeedChannel(" + ConstStr(channelName) + ", " + ConstStr(channelLabel) + ");");
				WriteLine("");
				XmlNode connections = node.ChildNodes[0];
				foreach(XmlNode conn in connections.ChildNodes) {
					string c_id = conn.Attributes["id"].Value;
					string feedType = conn.ChildNodes[0].Attributes["feed-type"].Value;
					string protocol = NodeValue(conn.ChildNodes[1]);

					string protocolValue = protocol == "TCP/IP" ? "FeedConnectionProtocol::TCP_IP" : "FeedConnectionProtocol::UDP_IP";
					string feedValueName = c_id.ToLower() + "_" + channelName.ToLower();
					string feedClassName = "FeedConnection_" + channelName + "_" + c_id;
					string feedValue = "'" + NodeValue(conn.ChildNodes[0]) + "'";

					WriteLine("\t\tif(this->AllowFeed(\"" + c_id + "\")) {");
					if(c_id == "H") {
						string ip = NodeValue(conn.ChildNodes[2]);
						string port = NodeValue(conn.ChildNodes[3]);

						WriteLine("\t\t\tFeedConnection *" + feedValueName + " = new " + feedClassName + "(" + ConstStr(c_id) + ", " + ConstStr(feedType) + ", " + feedValue + ", " + protocolValue + ", " + ConstStr(ip) + ", " + port + ");");
					} else {
						string srcIpA = NodeValue(conn.ChildNodes[2].ChildNodes[0]);
						string ipA = NodeValue(conn.ChildNodes[2].ChildNodes[1]);
						string portA = NodeValue(conn.ChildNodes[2].ChildNodes[2]);

						string srcIpB = NodeValue(conn.ChildNodes[3].ChildNodes[0]);
						string ipB = NodeValue(conn.ChildNodes[3].ChildNodes[1]);
						string portB = NodeValue(conn.ChildNodes[3].ChildNodes[2]);
					
						WriteLine("\t\t\tFeedConnection *" + feedValueName + " = new " + feedClassName + "(" + ConstStr(c_id) + ", " + ConstStr(feedType) + ", " + feedValue + ", " + protocolValue + ", " +
							ConstStr(srcIpA) + ", " + ConstStr(ipA) + ", " + portA + ", " + 
							ConstStr(srcIpB) + ", " + ConstStr(ipB) + ", " + portB +  
							");");
					}
					WriteLine("\t\t\t" + channelName.ToLower() + "->SetConnection(" + feedValueName + ");");
					WriteLine("\t\t}");
				}
				WriteLine("");
				WriteLine("\t\tthis->AddChannel(" + channelName.ToLower() + ");");
				WriteLine("\t}");
			}
			return true;
		}

		protected XmlNode GetTemplatesNode(XmlDocument doc) {
			foreach(XmlNode node in doc.ChildNodes) {
				if(node.Name == "templates")
					return node;
			}
			return null;
		}

		public bool Generate () {
			if(!File.Exists(ManagerSourceFileH)) {
				Console.WriteLine("source file '" + ManagerSourceFileH + "' does not exist.");
				return false;
			}
			if(!File.Exists(ManagerSourceFileCpp)) {
				Console.WriteLine("source file '" + ManagerSourceFileCpp + "' does not exist.");
				return false;
			}
			if(!File.Exists(SourceTypes)) {
				Console.WriteLine("asts source file '" + TypesFile + "' does not exist.");
				return false;
			}
			if(!File.Exists(AstsTemplateFile)) {
				Console.WriteLine("asts template xml file'" + AstsTemplateFile + "' does not exist.");
				return false;
			}
			if(!File.Exists(RobotCpp)) {
				Console.WriteLine("robot source file '" + RobotCpp + "' does not exist.");
				return false;
			}
			if(!File.Exists(AstsServerConfigFileName)) {
				Console.WriteLine("asts server config file '" + AstsServerConfigFileName + "' does not exist.");
			}

			ManagerHFile = new TextFile();
			ManagerCppFile = new TextFile();
			TypesFile = new TextFile();
			RobotCppFile = new TextFile();

			ManagerHFile.LoadFromFile(ManagerSourceFileH);
			ManagerCppFile.LoadFromFile(ManagerSourceFileCpp);
			TypesFile.LoadFromFile(SourceTypes);
			RobotCppFile.LoadFromFile(RobotCpp);

			ClearPreviouseGeneratedCode();

			GenerateDefinesCode();

			UseBmi = GetUseBmi();
			Console.WriteLine ("Using BMI = " + UseBmi);
			if (!UseBmi)
				Console.WriteLine ("WARNING!!!!!! BMI DISABLED!");

			Generate_ASTS();
			Generate_Forts();

			CheckSaveGeneratedFiles();

			return true;
		}

		bool GetUseBmi() {
			ManagerHFile.Line = 0;
			return ManagerHFile.FindString ("#define USE_BMI") != -1;
		}

		void GenerateDefinesCode() {
			ClearRegion("Defines_GeneratedCode");
			SetPosition("Defines_GeneratedCode");

			WriteLine("#define PRESENCE_MAP_INDEX0  0x0000000000000040L");
			WriteLine("#define PRESENCE_MAP_INDEX1  0x0000000000000020L");
			WriteLine("#define PRESENCE_MAP_INDEX2  0x0000000000000010L");
			WriteLine("#define PRESENCE_MAP_INDEX3  0x0000000000000008L");
			WriteLine("#define PRESENCE_MAP_INDEX4  0x0000000000000004L");
			WriteLine("#define PRESENCE_MAP_INDEX5  0x0000000000000002L");
			WriteLine("#define PRESENCE_MAP_INDEX6  0x0000000000000001L");

			WriteLine("#define PRESENCE_MAP_INDEX7  0x0000000000004000L");
			WriteLine("#define PRESENCE_MAP_INDEX8  0x0000000000002000L");
			WriteLine("#define PRESENCE_MAP_INDEX9  0x0000000000001000L");
			WriteLine("#define PRESENCE_MAP_INDEX10 0x0000000000000800L");
			WriteLine("#define PRESENCE_MAP_INDEX11 0x0000000000000400L");
			WriteLine("#define PRESENCE_MAP_INDEX12 0x0000000000000200L");
			WriteLine("#define PRESENCE_MAP_INDEX13 0x0000000000000100L");

			WriteLine("#define PRESENCE_MAP_INDEX14 0x0000000000400000L");
			WriteLine("#define PRESENCE_MAP_INDEX15 0x0000000000200000L");
			WriteLine("#define PRESENCE_MAP_INDEX16 0x0000000000100000L");
			WriteLine("#define PRESENCE_MAP_INDEX17 0x0000000000080000L");
			WriteLine("#define PRESENCE_MAP_INDEX18 0x0000000000040000L");
			WriteLine("#define PRESENCE_MAP_INDEX19 0x0000000000020000L");
			WriteLine("#define PRESENCE_MAP_INDEX20 0x0000000000010000L");

			WriteLine("#define PRESENCE_MAP_INDEX21 0x0000000040000000L");
			WriteLine("#define PRESENCE_MAP_INDEX22 0x0000000020000000L");
			WriteLine("#define PRESENCE_MAP_INDEX23 0x0000000010000000L");
			WriteLine("#define PRESENCE_MAP_INDEX24 0x0000000008000000L");
			WriteLine("#define PRESENCE_MAP_INDEX25 0x0000000004000000L");
			WriteLine("#define PRESENCE_MAP_INDEX26 0x0000000002000000L");
			WriteLine("#define PRESENCE_MAP_INDEX27 0x0000000001000000L");

			WriteLine("#define PRESENCE_MAP_INDEX28 0x0000004000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX29 0x0000002000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX30 0x0000001000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX31 0x0000000800000000L");
			WriteLine("#define PRESENCE_MAP_INDEX32 0x0000000400000000L");
			WriteLine("#define PRESENCE_MAP_INDEX33 0x0000000200000000L");
			WriteLine("#define PRESENCE_MAP_INDEX34 0x0000000100000000L");

			WriteLine("#define PRESENCE_MAP_INDEX35 0x0000400000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX36 0x0000200000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX37 0x0000100000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX38 0x0000080000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX39 0x0000040000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX40 0x0000020000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX41 0x0000010000000000L");

			WriteLine("#define PRESENCE_MAP_INDEX42 0x0040000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX43 0x0020000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX44 0x0010000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX45 0x0008000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX46 0x0004000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX47 0x0002000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX48 0x0001000000000000L");

			WriteLine("#define PRESENCE_MAP_INDEX49 0x4000000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX50 0x2000000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX51 0x1000000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX52 0x0800000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX53 0x0400000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX54 0x0200000000000000L");
			WriteLine("#define PRESENCE_MAP_INDEX55 0x0100000000000000L");

			WriteLine("#define NULL_MAP_INDEX0      0x0000000000000001L");
			WriteLine("#define NULL_MAP_INDEX1      0x0000000000000002L");
			WriteLine("#define NULL_MAP_INDEX2      0x0000000000000004L");
			WriteLine("#define NULL_MAP_INDEX3      0x0000000000000008L");
			WriteLine("#define NULL_MAP_INDEX4      0x0000000000000010L");
			WriteLine("#define NULL_MAP_INDEX5      0x0000000000000020L");
			WriteLine("#define NULL_MAP_INDEX6      0x0000000000000040L");
			WriteLine("#define NULL_MAP_INDEX7      0x0000000000000080L");
			WriteLine("#define NULL_MAP_INDEX8      0x0000000000000100L");
			WriteLine("#define NULL_MAP_INDEX9      0x0000000000000200L");
			WriteLine("#define NULL_MAP_INDEX10     0x0000000000000400L");
			WriteLine("#define NULL_MAP_INDEX11     0x0000000000000800L");
			WriteLine("#define NULL_MAP_INDEX12     0x0000000000001000L");
			WriteLine("#define NULL_MAP_INDEX13     0x0000000000002000L");
			WriteLine("#define NULL_MAP_INDEX14     0x0000000000004000L");
			WriteLine("#define NULL_MAP_INDEX15     0x0000000000008000L");

			WriteLine("#define NULL_MAP_INDEX16     0x0000000000010000L");
			WriteLine("#define NULL_MAP_INDEX17     0x0000000000020000L");
			WriteLine("#define NULL_MAP_INDEX18     0x0000000000040000L");
			WriteLine("#define NULL_MAP_INDEX19     0x0000000000080000L");
			WriteLine("#define NULL_MAP_INDEX20     0x0000000000100000L");
			WriteLine("#define NULL_MAP_INDEX21     0x0000000000200000L");
			WriteLine("#define NULL_MAP_INDEX22     0x0000000000400000L");
			WriteLine("#define NULL_MAP_INDEX23     0x0000000000800000L");
			WriteLine("#define NULL_MAP_INDEX24     0x0000000001000000L");
			WriteLine("#define NULL_MAP_INDEX25     0x0000000002000000L");
			WriteLine("#define NULL_MAP_INDEX26     0x0000000004000000L");
			WriteLine("#define NULL_MAP_INDEX27     0x0000000008000000L");
			WriteLine("#define NULL_MAP_INDEX28     0x0000000010000000L");
			WriteLine("#define NULL_MAP_INDEX29     0x0000000020000000L");
			WriteLine("#define NULL_MAP_INDEX30     0x0000000040000000L");
			WriteLine("#define NULL_MAP_INDEX31     0x0000000080000000L");

			WriteLine("#define NULL_MAP_INDEX32     0x0000000100000000L");
			WriteLine("#define NULL_MAP_INDEX33     0x0000000200000000L");
			WriteLine("#define NULL_MAP_INDEX34     0x0000000400000000L");
			WriteLine("#define NULL_MAP_INDEX35     0x0000000800000000L");
			WriteLine("#define NULL_MAP_INDEX36     0x0000001000000000L");
			WriteLine("#define NULL_MAP_INDEX37     0x0000002000000000L");
			WriteLine("#define NULL_MAP_INDEX38     0x0000004000000000L");
			WriteLine("#define NULL_MAP_INDEX39     0x0000008000000000L");
			WriteLine("#define NULL_MAP_INDEX40     0x0000010000000000L");
			WriteLine("#define NULL_MAP_INDEX41     0x0000020000000000L");
			WriteLine("#define NULL_MAP_INDEX42     0x0000040000000000L");
			WriteLine("#define NULL_MAP_INDEX43     0x0000080000000000L");
			WriteLine("#define NULL_MAP_INDEX44     0x0000100000000000L");
			WriteLine("#define NULL_MAP_INDEX45     0x0000200000000000L");
			WriteLine("#define NULL_MAP_INDEX46     0x0000400000000000L");
			WriteLine("#define NULL_MAP_INDEX47     0x0000800000000000L");

			WriteLine("#define NULL_MAP_INDEX48     0x0001000000000000L");
			WriteLine("#define NULL_MAP_INDEX49     0x0002000000000000L");
			WriteLine("#define NULL_MAP_INDEX50     0x0004000000000000L");
			WriteLine("#define NULL_MAP_INDEX51     0x0008000000000000L");
			WriteLine("#define NULL_MAP_INDEX52     0x0010000000000000L");
			WriteLine("#define NULL_MAP_INDEX53     0x0020000000000000L");
			WriteLine("#define NULL_MAP_INDEX54     0x0040000000000000L");
			WriteLine("#define NULL_MAP_INDEX55     0x0080000000000000L");
			WriteLine("#define NULL_MAP_INDEX56     0x0100000000000000L");
			WriteLine("#define NULL_MAP_INDEX57     0x0200000000000000L");
			WriteLine("#define NULL_MAP_INDEX58     0x0400000000000000L");
			WriteLine("#define NULL_MAP_INDEX59     0x0800000000000000L");
			WriteLine("#define NULL_MAP_INDEX60     0x1000000000000000L");
			WriteLine("#define NULL_MAP_INDEX61     0x2000000000000000L");
			WriteLine("#define NULL_MAP_INDEX62     0x4000000000000000L");
			WriteLine("#define NULL_MAP_INDEX63     0x8000000000000000L");
		}

		void Generate_ASTS() {
			XmlDocument doc = new XmlDocument();
			doc.Load(AstsTemplateFile);

			TemplatesNode = GetTemplatesNode(doc);
			if(TemplatesNode == null)
				throw new ArgumentException("Cannot find 'templates' node in asts templates file");

			PrepareForAsts();
			GenerateTemplatesCodeAsts();
			GenerateAddChannelsCode_ASTS();
		}

		void PrepareForAsts() { 
			Prefix = "Asts";
			Mode = GeneratorMode.Asts;
			Message_Info_Structures_Definition_GeneratedCode = "Asts_Message_Info_Structures_Definition_GeneratedCode";
			Structure_Objects_Declaration_GeneratedCode = "Asts_Structure_Objects_Declaration_GeneratedCode";
			Decode_Methods_Definition_GeneratedCode = "Asts_Decode_Methods_Definition_GeneratedCode";
			Encode_Methods_Declaration_GeneratedCode = "Asts_Encode_Methods_Declaration_GeneratedCode";
			Encode_Methods_Definition_GeneratedCode = "Asts_Encode_Methods_Definition_GeneratedCode";
			Print_Methods_Definition_GeneratedCode = "Asts_Print_Methods_Definition_GeneratedCode";
			Print_Methods_Declaration_GeneratedCode = "Asts_Print_Methods_Declaration_GeneratedCode";
			Declare_AllocationInfo_GeneratedCode = "Asts_Declare_AllocationInfo_GeneratedCode";
			AddDefaultChannels_GeneratedCode = "Asts_AddDefaultChannels_GeneratedCode";

			SnapshotInfoFields = new List<SnapshotFieldInfo>();
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RptSeq"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastFragment"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RouteFirst"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastMsgSeqNumProcessed"));
			//SnapshotInfoFields.Add(new SnapshotFieldInfo("", "SendingTime"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "Symbol"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "TradingSessionID"));

			ClearStructures();
		}

		void PrepareForForts() {
			Prefix = "Forts";
			Mode = GeneratorMode.Spectra;
			Message_Info_Structures_Definition_GeneratedCode = "Forts_Message_Info_Structures_Definition_GeneratedCode";
			Structure_Objects_Declaration_GeneratedCode = "Forts_Structure_Objects_Declaration_GeneratedCode";
			Decode_Methods_Definition_GeneratedCode = "Forts_Decode_Methods_Definition_GeneratedCode";
			Encode_Methods_Declaration_GeneratedCode = "Forts_Encode_Methods_Declaration_GeneratedCode";
			Encode_Methods_Definition_GeneratedCode = "Forts_Encode_Methods_Definition_GeneratedCode";
			Print_Methods_Definition_GeneratedCode = "Forts_Print_Methods_Definition_GeneratedCode";
			Print_Methods_Declaration_GeneratedCode = "Forts_Print_Methods_Declaration_GeneratedCode";
			Declare_AllocationInfo_GeneratedCode = "Forts_Declare_AllocationInfo_GeneratedCode";
			AddDefaultChannels_GeneratedCode = "Forts_AddDefaultChannels_GeneratedCode";

			SnapshotInfoFields = new List<SnapshotFieldInfo>();
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "RptSeq"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastFragment"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "LastMsgSeqNumProcessed"));
			//SnapshotInfoFields.Add(new SnapshotFieldInfo("", "SendingTime"));
			SnapshotInfoFields.Add(new SnapshotFieldInfo("", "SecurityID"));

			ClearStructures();
		}

		void Generate_Forts() {
			XmlDocument doc = new XmlDocument();
			doc.Load(SpectraTemplateFile);

			TemplatesNode = GetTemplatesNode(doc);
			if(TemplatesNode == null)
				throw new ArgumentException("Cannot find 'templates' node in spectra templates file");

			PrepareForForts();
			GenerateTemplatesCodeSpectra();
			GenerateAddChannelsCode_FORTS();
		}

		void CheckSaveGeneratedFiles() {
			if(!ManagerHFile.Modified)
				Console.WriteLine(ManagerSourceFileH + " - no changes were made. skip update source file.");
			else
				ManagerHFile.Save();
			if(!ManagerCppFile.Modified)
				Console.WriteLine(ManagerSourceFileCpp + " - no changes were made. skip update source file.");
			else
				ManagerCppFile.Save();
			if(!TypesFile.Modified)
				Console.WriteLine(SourceTypes + " - no changes were made. skip update source file.");
			else
				TypesFile.Save();
			if(!RobotCppFile.Modified)
				Console.WriteLine(RobotCppFile + " - no changes were made. skip update source file.");
			else
				RobotCppFile.Save();
		}

		string Message_Info_Structures_Definition_GeneratedCode = "Message_Info_Structures_Definition_GeneratedCode";
		string Structure_Objects_Declaration_GeneratedCode = "Structure_Objects_Declaration_GeneratedCode";
		string Decode_Methods_Definition_GeneratedCode = "Decode_Methods_Definition_GeneratedCode";
		string Get_Free_Item_Methods_GeneratedCode = "Get_Free_Item_Methods_GeneratedCode";
		string Encode_Methods_Definition_GeneratedCode = "Encode_Methods_Definition_GeneratedCode";
		string Encode_Methods_Declaration_GeneratedCode = "Encode_Methods_Declaration_GeneratedCode";
		string String_Constant_Declaration_GeneratedCode = "String_Constant_Declaration_GeneratedCode";
		string Print_Methods_Definition_GeneratedCode = "Print_Methods_Definition_GeneratedCode";
		string Print_Methods_Declaration_GeneratedCode = "Print_Methods_Declaration_GeneratedCode";
		string AddDefaultChannels_GeneratedCode = "AddDefaultChannels_GeneratedCode";
		string Declare_AllocationInfo_GeneratedCode = "Declare_AllocationInfo_GeneratedCode";

		private  void ClearPreviouseGeneratedCode () {
			string[] keywords = new string[] { 
				Message_Info_Structures_Definition_GeneratedCode,
				Structure_Objects_Declaration_GeneratedCode,
				Get_Free_Item_Methods_GeneratedCode,
				Encode_Methods_Definition_GeneratedCode,
				Encode_Methods_Declaration_GeneratedCode,
				String_Constant_Declaration_GeneratedCode,
				Print_Methods_Declaration_GeneratedCode,
				Print_Methods_Definition_GeneratedCode,
				AddDefaultChannels_GeneratedCode
			};
			foreach(string keyword in keywords) {
				ClearRegion(keyword);
			}
		}

		private void ClearRegion(string keyword) {
			SetPosition(keyword);
			int startingIndex = CurrentFile.Line;
			int endIndex = GetEndRegionLineIndex(startingIndex);
			int count = endIndex - startingIndex;
			for(int i = 0; i < count; i++) {
				CurrentFile.Remove(startingIndex);
			}
		}

		private  int GetEndRegionLineIndex (int startIndex) { 
			int index = startIndex;
			for(int i = startIndex; i < Strings.Count; i++) {
				if(Strings[i].Contains("#pragma") && Strings[i].Contains("endregion"))
					return index;
				index++;
			}
			return Strings.Count;
		}

		private  int GetKeywordLineIndex (string keyword) {
			if(SetPosition(keyword))
				return CurrentFile.Line;
			return -1;
		}

		List<ConstantStringInfo> ConstantStrings { get; set; }

		void WriteDeclareAllocationInfoCode() { 
			ClearRegion(Declare_AllocationInfo_GeneratedCode);
			SetPosition(Declare_AllocationInfo_GeneratedCode);
			WriteLine("\t" + Prefix + "ObjectsAllocationInfo *m_" + Prefix.ToLower() + "AllocationInfo;");
			WriteLine("\t" + Prefix + "SnapshotInfo *m_" + Prefix.ToLower() + "SnapshotInfo;");
		}

		private  void GenerateTemplatesCodeAsts () {
			Console.WriteLine("generate asts...");
			WriteDeclareAllocationInfoCode();
			WriteStructuresDefinitionCode(TemplatesNode, true);
			WriteStructuresDeclarationCode();
			ConstantStrings = GetConstantStrings(TemplatesNode);
			WriteStringConstantDeclarationCode(TemplatesNode);
			WriteGetFreeItemCode(TemplatesNode);
			WriteReleaseItemCode(TemplatesNode);

			WriteEncodeMethodsCode(TemplatesNode);
			WriteHeaderParsingCode(TemplatesNode);
			WriteGetTotNumReportsMethod(TemplatesNode);
			WriteDecodeMethodsCode(TemplatesNode);
			WritePrintMethodsCode(TemplatesNode);
			Console.WriteLine("done.");
		}

		private  void GenerateTemplatesCodeSpectra () {
			Console.WriteLine("generate forts...");
			WriteDeclareAllocationInfoCode();
			WriteStructuresDefinitionCode(TemplatesNode, true);
			WriteStructuresDeclarationCode();
			//ConstantStrings = GetConstantStrings(TemplatesNode);
			//WriteStringConstantDeclarationCode(TemplatesNode);
			WriteGetFreeItemCode(TemplatesNode);
			WriteReleaseItemCode(TemplatesNode);

			WriteEncodeMethodsCode(TemplatesNode);
			WriteHeaderParsingCode(TemplatesNode);
			WriteGetTotNumReportsMethod(TemplatesNode);
			WriteDecodeMethodsCode(TemplatesNode);
			WritePrintMethodsCode(TemplatesNode);

			Console.WriteLine("done.");
		}

		class ConstantStringInfo {
			public XmlNode Node { get; set; }
			public string Name { get { return Node.Attributes["name"].Value; } }
			public string Value { get { return Node.ChildNodes[0].Attributes["value"].Value; } }
			public string FieldName { get { return Name + "ConstString"; } }
		}

		private bool HasConstString(XmlNode node) {
			return node.Name == "string" && node.ChildNodes.Count == 1 && (node.ChildNodes[0].Name == "default"/* || node.ChildNodes[0].Name == "constant"*/);
		}

		private List<ConstantStringInfo> GetConstantStrings(XmlNode node) {
			List<ConstantStringInfo> res = new List<ConstantStringInfo>();
			GetConstantStrings(node, res);
			return res;
		}

		private void GetConstantStrings(XmlNode node, List<ConstantStringInfo> list) {
			foreach(XmlNode child in node.ChildNodes) {
				if(HasConstString(child))
					list.Add(new ConstantStringInfo() { Node = child });
				GetConstantStrings(child, list);
			}
		}

		private void WriteStringConstantDeclarationCode(XmlNode node) {
			SetPosition(String_Constant_Declaration_GeneratedCode);
			WriteLine("public:");
			foreach(ConstantStringInfo info in ConstantStrings) {
				int length = info.Value.Length / 8;
				WriteLine("\tchar\t" + info.FieldName + "[" + (length * 8 + 8) + "];");
				WriteLine("\tstatic const UINT\t" + info.FieldName + "Length = " + info.Value.Length + ";");
			}
			WriteLine("private:");
			WriteLine("");
			WriteLine("\tvoid InitializeConstantStrings() {");
			foreach(ConstantStringInfo info in ConstantStrings) {
				WriteLine("\t\tsprintf(" + info.FieldName + ", \"" + info.Value + "\");");
			}
			WriteLine("\t}");
		}

		private  void WriteEncodeMethodsCode (XmlNode templatesNode) {
			List<StructureInfo> st = GetStructures(TemplatesNode);
			ClearRegion(Encode_Methods_Declaration_GeneratedCode);
			SetPosition(Encode_Methods_Declaration_GeneratedCode);
			foreach(StructureInfo info in st) {
				if(info.IsSequence)
					continue;
				WriteEncodeMethodDeclarationMethodCode(info);
			}
			ClearRegion(Encode_Methods_Definition_GeneratedCode);
			SetPosition(Encode_Methods_Definition_GeneratedCode);
			foreach(StructureInfo info in st) {
				if(info.IsSequence)
					continue;
				WriteEncodeMethodCode(info);
			}
		}

		private void WriteEncodeMethodDeclarationMethodCode (StructureInfo info) {
			WriteLine("\tvoid " + info.EncodeMethodName + "(" + info.Name + "* info);");
		}

		private void WriteEncodeMethodCode (StructureInfo info) {
			WriteLine("void FastProtocolManager::" + info.EncodeMethodName + "(" + info.Name + "* info) {");
			WriteLine("\tWritePresenceMap(info->PresenceMap); // Presence Map hack");
			WriteLine("\tWriteUInt32_Mandatory(" + info.Node.Attributes["id"].Value + ");");
			int presenceByteCount = CalcPresenceMapByteCount(info.Node);
			if(GetMaxPresenceBitCount(info.Node) > 0)
				WriteLine("\tWritePresenceMap" + presenceByteCount + "(info->PresenceMap);");
			foreach(XmlNode node in info.Node.ChildNodes) {
				info.Parent = null;
				WriteEncodeValueCode(node, info, "\t");
			}
			WriteLine("}");
		}

		private void WriteNullValueCode(string tabs, XmlNode value) {
			if(IsString(value))
				WriteLine(tabs + "this->WriteNullString();");
			else 
				WriteLine(tabs + "this->WriteNull();");
		}
		bool IsByteVector(XmlNode field) {
			return field.Name == "byteVector" || (HasAttribute(field, "charset") && field.Attributes["charset"].Value == "unicode");
		}
		bool IsString(XmlNode field) {
			return field.Name == "string" && (!HasAttribute(field, "charset") || field.Attributes["charset"].Value != "unicode");
		}
		private  void WriteEncodeValueCode (XmlNode field, StructureInfo si, string tabs) {
			bool nullCheck = ShouldWriteNullCheckCode(field);
			bool presenceCheck = ShouldWriteCheckPresenceMapCode(field);
			if(!CanParseValue(field))
				return;
			if(presenceCheck) {
				string bracket = nullCheck ? " {" : "";
				string checkPresenceMethodName = HasOptionalPresence(field)? "CheckOptionalFieldPresence": "CheckMandatoryFieldPresence";
				WriteLine(tabs + "if(" + checkPresenceMethodName + "(" + si.InCodeValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(field) + "))" + bracket);

				tabs += "\t";
			}
			if(nullCheck) {
				int nullIndex = CalcNullIndex(field);
				WriteLine(tabs + "if((" + si.InCodeValueName + "->NullMap & NULL_MAP_INDEX" + nullIndex + ") != 0)");
				WriteNullValueCode(tabs + "\t", field);

				if(field.Name == "sequence")
					WriteLine(tabs + "else {");
				else 
					WriteLine(tabs + "else");

				tabs += "\t";
			}
			if(IsString(field))
				WriteStringEncodeMethodCode(field, si, tabs);
			else if(field.Name == "uInt32")
				WriteUint32EncodeMethodCode(field, si, tabs);
			else if(field.Name == "int32")
				WriteInt32EncodeMethodCode(field, si, tabs);
			else if(field.Name == "uInt64")
				WriteUint64EncodeMethodCode(field, si, tabs);
			else if(field.Name == "int64")
				WriteInt64EncodeMethodCode(field, si, tabs);
			else if(field.Name == "decimal")
				WriteDecimalEncodeMethodCode(field, si, tabs);
			else if(IsByteVector(field))
				WriteByteVectorEncodeMethodCode(field, si, tabs);
			else if(field.Name == "sequence") {
				WriteSequenceEncodeMethodCode(field, si, tabs);
				if(nullCheck) {
					tabs = tabs.Substring(1);
					WriteLine(tabs + "}");
				}

			} else if(field.Name == "length") {
				// Do nothing
			}
			if(nullCheck && presenceCheck) {
				tabs = tabs.Substring(1);
				WriteLine(tabs + "}");
			}
			if(presenceCheck) {
				tabs = tabs.Substring(1);
			}
		}

		private  void WriteSequenceEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string itemInfo = GetIemInfoPrefix(field) + "ItemInfo";
			StructureInfo info = new StructureInfo() { InCodeValueName = "(*" + itemInfo + ")", NameCore = si.NameCore + ItemName(field), IsSequence = true };
			info.Prefix = Prefix;
			StructureInfo item = GetOriginalStruct(field);
			if(item == null)
				item = info;
			else
				item.Prefix = Prefix;
			string methodName = HasOptionalPresence(field)? "WriteUInt32_Optional": "WriteUInt32_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + "Count);");
			WriteLine(tabs + item.Name + " **" + itemInfo + " = " + si.InCodeValueName + "->" + Name(field) + ";");
			WriteLine(tabs + "for(int i = 0; i < " + si.InCodeValueName + "->" + Name(field) + "Count; i++) {");
			if(GetMaxPresenceBitCount(field) > 0) {
				WriteLine(tabs + "\tWritePresenceMap((*" + itemInfo + ")->PresenceMap); // Presence Map hack");
				WriteLine("");
			}
			foreach(XmlNode node in field.ChildNodes) {
				WriteEncodeValueCode(node, info, tabs + "\t");
			}
			WriteLine(tabs + "\t" + itemInfo + "++;");
			WriteLine(tabs + "}");
		}

		private  void WriteByteVectorEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field)? "WriteByteVector_Optional": "WriteByteVector_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ", " + si.InCodeValueName + "->" + Name(field) + "Length);");
		}

		private  void WriteDecimalEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteDecimal_Optional" : "WriteDecimal_Mandatory";
			WriteLine(tabs + methodName + "(&(" + si.InCodeValueName + "->" + Name(field) + "));");
		}

		private  void WriteInt64EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteInt64_Optional" : "WriteInt64_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteUint64EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteUInt64_Optional" : "WriteUInt64_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteInt32EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteInt32_Optional" : "WriteInt32_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteUint32EncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteUInt32_Optional" : "WriteUInt32_Mandatory";
			WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ");");
		}

		private  void WriteStringEncodeMethodCode (XmlNode field, StructureInfo si, string tabs) {
			string methodName = HasOptionalPresence(field) ? "WriteString_Optional" : "WriteString_Mandatory";
			if(HasConstantAttribute(field))
				WriteLine(tabs + methodName + "(\"" + GetFieldConstantValue(field) + "\", " + GetFieldConstantValue(field).Length + ");");
			else if(HasAttribute(field, "fixed_size"))
				WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ", " + field.Attributes["fixed_size"].Value + ");");
			else 
				WriteLine(tabs + methodName + "(" + si.InCodeValueName + "->" + Name(field) + ", " + si.InCodeValueName + "->" + Name(field) + "Length);");
		}

		private  List<XmlNode> GetAllMessages (XmlNode templatesNode) {
			List<XmlNode> res = new List<XmlNode>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template")
					res.Add(node);
			}
			return res;
		}

		private  void WriteGetFreeItemCode (XmlNode templatesNode) {
			SetPosition(Get_Free_Item_Methods_GeneratedCode);

			WriteLine("public:");

			WriteLine("\tinline " + Prefix + "SnapshotInfo* GetFree" + Prefix + "SnapshotInfo() {");
			WriteLine("\t\tthis->m_" + Prefix.ToLower() + "SnapshotInfo->LastFragment = 0;");
			WriteLine("\t\tthis->m_" + Prefix.ToLower() + "SnapshotInfo->LastMsgSeqNumProcessed = -1;");
			if(SnapshotInfoFields.FirstOrDefault((f) => f.FieldName == "RouteFirst") != null)
				WriteLine("\t\tthis->m_" + Prefix.ToLower() + "SnapshotInfo->RouteFirst = 0;");
			WriteLine("\t\tthis->m_" + Prefix.ToLower() + "SnapshotInfo->RptSeq = -1;");
			WriteLine("\t\treturn this->m_" + Prefix.ToLower() + "SnapshotInfo;");
			WriteLine("\t}");

			foreach(StructureInfo str in Structures) {
				WriteLine("\tinline " + str.Name + "* " + str.GetFreeMethodName + "() {");
				if (!str.AllowCache)
					WriteLine ("\t\treturn this->" + str.ValueName + "->NewItemUnsafe();");
				else
					WriteLine ("\t\treturn this->" + str.CachedValueName + ";");
				WriteLine("\t}");
				WriteLine("");
				WriteLine("\tinline AutoAllocatePointerList<" + str.Name + ">* " + str.GetListMethodName + "() {");
				WriteLine("\t\treturn this->" + str.ValueName + ";");
				WriteLine("\t}");
				WriteLine("");
			}

			foreach (StructureInfo str in Structures) {
				WriteLine("\tinline void " + str.PrefetchMethodName + "() {");
				if (!str.AllowCache) {
					WriteLine ("\t\t" + str.Name + " *item = " + "this->" + str.ValueName + "->Start()->Data();");
				} else {
					WriteLine ("\t\t" + str.Name + " *item = " + "this->" + str.CachedValueName + ";");
				}
				WriteLine ("\t\tfor(int i = 0; i < sizeof(" + str.Name + "); i+= 64)");
				WriteLine ("\t\t\t__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);");
				WriteLine("\t}");
				WriteLine("");
			}

			WriteLine("private:");
		}

		public string NameWithParent(XmlNode node) {
			string name = string.Empty;
			while(node.Name != "templates") {
				if(node.Name == "template")
					name = GetTemplateName(node) + name;
				else 
					name = ItemName(node) + name;
				node = node.ParentNode;
			}
			return name;
		}

		private void WriteReleaseItemCode (XmlNode templatesNode) {
			foreach(StructureInfo str in Structures) {
				WriteLine("\tvoid " + str.ReleaseMethodName + "() {");
				WriteLine("\t\tstatic_cast<" + str.Name + "*>(this->LastDecodeInfo())->ReleaseUnused();");
				WriteLine("\t}");
			}
			WriteLine("\tinline void Reset" + Prefix + "() {");
			List<DecodeMessageInfo> list = GetDecodeMessageMethods(templatesNode);
			WriteSelector("\t\t", list, new WriteConditionDelegate(WriteReleaseMethod));
			WriteLine("\t}");
		}

		public class StructureInfo {
			public StructureInfo() { 
				Prefix = "Fast";
			}
			public string Prefix { get; set; }
			public string Name {
				get {
					return Prefix + NameCore + Suffix;
				}
			}

			public string PresenceIndicesClassName { 
				get { return Name + "PresenceIndices"; }
			}

			public string NullIndicesClassName { 
				get{ return Name + "NullIndices"; }
			}

			public int TemplateId { get { return int.Parse(Node.Attributes ["id"].Value); } }

			public XmlNode Node { get; set; }

			public string NameCore { get; set; }

			public bool IsSequence { get; set; }
			public bool AllowCache { get; set; }

			public string ValueName { 
				get { 
					return "m_" + Prefix.ToLower() + NameCore + (IsSequence ? "Items" : ""); 
				} 
			}

			public string PrevValueName {
				get {
					return "m_prev" + Prefix.ToLower() + NameCore + (IsSequence ? "Item" : "") + "Info"; 
				}
			}

			public string CachedValueName {
				get {
					return "m_cached" + Prefix.ToLower() + NameCore + (IsSequence ? "Item" : "") + "Info"; 
				}
			}

			public string CurrentItemValueName {
				get {
					return ValueName + "CurrentItem";
				}
			}

			public string MaxItemCountValueName {
				get { return ValueName + "MaxCount"; }
			}

			public string Suffix {
				get { return IsSequence ? "ItemInfo" : "Info"; }
			}

			public string PrefetchMethodName { 
				get { return "Prefetch" + Prefix + NameCore + Suffix; }
			}

			public string GetFreeMethodName {
				get { return "GetFree" + Prefix + NameCore + Suffix; }
			}

			public string GetListMethodName { 
				get{ return "Get" + Prefix + NameCore + Suffix + "Pool"; }
			}

			public string AllocatePoolMethodName { 
				get{ return "Allocate" + NameCore + Suffix + "Pool"; }
			}

			public string ReleaseMethodName { 
				get { return "Release" + Prefix + NameCore + Suffix; }
			}

			public string EncodeMethodName {
				get { return "Encode" + Prefix + NameCore + Suffix; }
			}

			public StructureInfo Parent { get; set; }
			List<StructureInfo> incStruct;
			public List<StructureInfo> IncrementalStructures { 
				get { 
					if(incStruct == null)
						incStruct = new List<StructureInfo>();
					return incStruct;
				}
			}
			public bool HasIncrementalStruct(XmlNode node) {
				if(IncrementalStructures.Count == 0)
					return false;
				XmlNode parentNode = node.ParentNode;
				if(parentNode == null || parentNode.Attributes["name"] == null)
					return false;
				//Console.WriteLine("Seeking inc " + parentNode.Attributes["name"].Value);
				foreach(StructureInfo info in IncrementalStructures) {
					XmlNode pn = info.Node.ParentNode;
					//if(pn == null)
					//	Console.WriteLine("pn == null");
					//Console.WriteLine("Check " + pn.Attributes["name"].Value);
					if(pn == parentNode) {
						//Console.WriteLine("found.");
						return true;
					}
				}
				//Console.WriteLine("not found");
				return false;
			}
			public string InStructFieldName { get; set; }
			string inCodeValueName = "info";
			public string InCodeValueName { 
				get { 
					if(Parent == null)
						return inCodeValueName;
					return Parent.InCodeValueName + "->" + InStructFieldName;
				}
				set { 
					inCodeValueName = value;
				}
			}
			public List<XmlNode> Fields { get; set; }
		}

		private  List<StructureInfo> GetStructures (XmlNode templatesNode) {
			List<StructureInfo> res = new List<StructureInfo>();
			GetStructures(res, templatesNode, true);
			GetStructures(res, templatesNode, false);
			return res;
		}

		private void GetStructures(List<StructureInfo> res, XmlNode templatesNode, bool excludeIncremental) {
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					string nameCore = GetTemplateName(node);
					if(excludeIncremental && nameCore.Contains("Increment"))
						continue;
					else if(!excludeIncremental && !nameCore.Contains("Increment"))
						continue;
					List<StructureInfo> child = new List<StructureInfo>();
					GetSequenceStructureNames(nameCore, node, child);
					StructureInfo info = new StructureInfo() { NameCore = nameCore, Node = node };
					info.Prefix = Prefix;
					info.AllowCache = HasAttribute (node, "cache") && node.Attributes["cache"].Value == "true";
					foreach(StructureInfo c in child) {
						res.Add(c);
						c.Parent = info;
					}
					info.Fields = new List<XmlNode>();
					foreach(XmlNode field in node.ChildNodes) {
						info.Fields.Add(field);
					}
					res.Add(info);
				}
			}
		}

		private  void GetSequenceStructureNames (string parentStructNameCore, XmlNode parent, List<StructureInfo> res) {
			foreach(XmlNode node in parent.ChildNodes) {
				if(node.Name != "sequence")
					continue;
				string nameCore = parentStructNameCore + ItemName(node);
				List<StructureInfo> child = new List<StructureInfo>();
				GetSequenceStructureNames(nameCore, node, child);
				StructureInfo info = new StructureInfo() { IsSequence = true, NameCore = nameCore, Node = node }; 
				info.Prefix = Prefix;
				foreach(StructureInfo c in child) {
					res.Add(c);
					c.Parent = info;
				}
				info.Fields = new List<XmlNode>();
				foreach(XmlNode field in node.ChildNodes) {
					info.Fields.Add(field);
				}
				res.Add(info);
			}
		}

		private  void WriteStructuresDeclarationCode () {
			ClearRegion(Structure_Objects_Declaration_GeneratedCode);
			SetPosition(Structure_Objects_Declaration_GeneratedCode);

			foreach(StructureInfo str in Structures) {
				WriteLine("\tAutoAllocatePointerList<" + str.Name + ">\t*" + str.ValueName + ";");
			}
			foreach (StructureInfo str in structures) {
				if (!str.AllowCache)
					continue;
				WriteLine ("\t" + str.Name + "\t*" + str.CachedValueName + ";");
			}
			foreach(StructureInfo str in Structures) {
				WriteLine("\t" + str.Name + "\t*" + str.PrevValueName + ";");
			}

			WriteLine("");
			WriteLine("\tvoid Initialize" + Prefix + "MessageInfo() {");
			foreach(StructureInfo str in structures) {
				WriteLine("\t\tthis->" + str.ValueName + " = this->m_" + Prefix.ToLower() + "AllocationInfo->" + str.GetListMethodName + "();");
			}
			foreach (StructureInfo str in structures) {
				if (!str.AllowCache)
					continue;
				WriteLine("\t\tthis->" + str.CachedValueName + " = this->" + str.ValueName + "->NewItemUnsafe();");
			}
			foreach(StructureInfo str in structures) {
				WriteLine("\t\tthis->" + str.PrevValueName + " = this->" + str.GetFreeMethodName + "();");
			}
			WriteLine("\t}");

			WriteLine("");
		}

		private List<XmlNode> GetTemplates(XmlNode templatesNode) {
			List<XmlNode> res = new List<XmlNode>();

			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template")
					res.Add(node);
			}
			return res;
		}

		private List<string> CollectHeaderTags(XmlNode templatesNode) {
			List<string> headerTags = new List<string>();
			List<XmlNode> templates = GetTemplates(templatesNode);
			 
			for(int i = 0; i < templates[0].ChildNodes.Count; i++) {
				string tagId = templates[0].ChildNodes[i].Attributes["id"].Value;
				//Console.WriteLine("checking " + tagId);
				for(int j = 1; j < templates.Count; j++) {
					if(i >= templates[j].ChildNodes.Count)
						return headerTags;
					string tagId2 = templates[j].ChildNodes[i].Attributes["id"].Value;
					if(tagId != tagId2) {
						//Console.WriteLine("non header tag expected " + tagId + " but found " + tagId2);
						return headerTags;
					}
				}
				//Console.WriteLine("add header tag " + templates[0].ChildNodes[i].Attributes["name"].Value);
				headerTags.Add(templates[0].ChildNodes[i].Attributes["id"].Value);
			}
			return headerTags;
		}

		protected List<string> HeaderTags { get; set; }
		private void WriteHeaderParsingCode(XmlNode templatesNode) {
			ClearRegion(Decode_Methods_Definition_GeneratedCode);
			SetPosition(Decode_Methods_Definition_GeneratedCode);

			WriteLine("\tinline void Decode" + Prefix + "Header() {"); 
			WriteLine("");
			WriteLine("\t\tthis->m_presenceMap = this->ParsePresenceMap();");
			if(UseBmi)
				WriteLine("\t\tthis->m_templateId = ReadUInt32_Mandatory_BMI();");
			else 
				WriteLine("\t\tthis->m_templateId = ReadUInt32_Mandatory_Simple();");
			WriteLine("\t}");
			WriteLine("");
		}

		private  void WriteDecodeMethodsCode (XmlNode templatesNode) {
			WriteLine("\tinline void* Decode" + Prefix + "UnsupportedMessage() { return 0; }");
			WriteLine("\tinline " + Prefix + "SnapshotInfo* Get" + Prefix + "SnapshotInfoUnsupported() { return 0; }");
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				ParseTemplateNode(node, GetTemplateName(node));
			}
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				WriteGetSnapshotInfoMethod(node, GetTemplateName(node));
			}
			WriteEntireMethodsCode(templatesNode);
		}

		private void WritePrintMethodsCode(XmlNode templatesNode) {
			ClearRegion(Print_Methods_Declaration_GeneratedCode);
			SetPosition(Print_Methods_Declaration_GeneratedCode);
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintDeclareTemplateNode(node, GetTemplateName(node));
				}
			}
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintXmlDeclareTemplateNode(node, GetTemplateName(node));
				}
			}

			ClearRegion(Print_Methods_Definition_GeneratedCode);
			SetPosition(Print_Methods_Definition_GeneratedCode);
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintTemplateNode(node, GetTemplateName(node));
				}
			}
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name == "template") {
					PrintXmlTemplateNode(node, GetTemplateName(node));
				}
			}
		}

		Dictionary<string, string> similarTemplates;
		protected Dictionary<string, string> TemplatesMap { 
			get { 
				if(similarTemplates == null) {
					similarTemplates = new Dictionary<string, string>();
					similarTemplates.Add("X-Generic", "W-Generic");

					similarTemplates.Add("X-OLR-FOND", "W-OLS-FOND");
					similarTemplates.Add("X-TLR-FOND", "W-TLS-FOND");
					similarTemplates.Add("X-OBR-FOND", "W-OBS-FOND");
					similarTemplates.Add("X-MSR-FOND", "W-Generic");

					similarTemplates.Add("X-OLR-CURR", "W-OLS-CURR");
					similarTemplates.Add("X-TLR-CURR", "W-TLS-CURR");
					similarTemplates.Add("X-OBR-CURR", "W-OBS-CURR");
					similarTemplates.Add("X-MSR-CURR", "W-Generic");

					similarTemplates.Add("DefaultIncrementalRefreshMessage", "DefaultSnapshotMessage");
				}
				return similarTemplates;
			}
		}

		StructureInfo FindIncrementalStructForTemplate(List<StructureInfo> str, StructureInfo snap){
			XmlNode snapeParentNode = snap.Node.ParentNode;
			if(snapeParentNode.Name != "template")
				return null;
			string snapParentName = snapeParentNode.Attributes["name"].Value;

			//Console.WriteLine("Seek similar for " + infoParentName);
			foreach(StructureInfo incInfo in str) { 
				XmlNode incParentNode = incInfo.Node.ParentNode;
				if(incParentNode.Name != "template")
					continue;
				string incParentName = incParentNode.Attributes["name"].Value;
				//Console.WriteLine("checking " + infoParentName2);

				string nameToCheck = string.Empty;
				if(!TemplatesMap.TryGetValue(incParentName, out nameToCheck))
					continue;
				if(nameToCheck != snapParentName)
					continue;
				if(snap.HasIncrementalStruct(incInfo.Node))
					continue;
				return incInfo;
			}
			
			return null;
		}

		List<StructureInfo> MergeStructures(List<StructureInfo> str) {
			List<StructureInfo> res = new List<StructureInfo>();
			List<StructureInfo> strToRemove = new List<StructureInfo>();
			foreach(StructureInfo info in str) {
				if(!info.IsSequence) {
					res.Add(info);
					continue;
				}

				while(true) {
					StructureInfo info2 = FindIncrementalStructForTemplate(str, info);
					if(info2 == null) {
						res.Add(info);
						break;
					}
					//Console.WriteLine("Found Incrementsal Structure for " + info.Name + " -> " + info2.Name);
					strToRemove.Add(info2);
					if(info.IncrementalStructures.Contains(info2)) {
						throw new Exception("Structure found twice");
					}
					info.IncrementalStructures.Add(info2);
				
					foreach(XmlNode node2 in info2.Fields) {
						bool foundField = false;
						foreach(XmlNode node in info.Fields) {
							if(Name(node) == Name(node2)) {
								foundField = true;
								break;
							}
						}
						if(!foundField)
							info.Fields.Add(node2);
					}
				}
			}
			foreach(StructureInfo info in strToRemove) {
				res.Remove(info);
			}
			return res;
		}

		private void WriteSnapshotInfoDefinitionCode(XmlNode templatesNode) {
			WriteLine("class " + Prefix + "SnapshotInfo {");
			WriteLine("public:");
			StructureFieldOffsetInfo offset = new StructureFieldOffsetInfo ();
			WriteLine("\tUINT64" + StuctFieldsSpacing + "PresenceMap;");
			WriteLine("\tUINT64" + StuctFieldsSpacing + "NullMap;");
			WriteLine("\tUINT32" + StuctFieldsSpacing + "TemplateId;");
			offset.Offset = 8 + 8 + 4;
			InitializeSnapshotInfoFields(templatesNode);
			foreach(SnapshotFieldInfo info in SnapshotInfoFields) {
				if (info.FieldType.ToLower() == "uint32" || info.FieldType.ToLower() == "int32") {
					CheckWriteAlignmentBy (offset, 4, false);
					WriteLine ("\t" + info.FieldType + StuctFieldsSpacing + info.FieldName + "; // offset = " + offset.Offset);
					offset.Offset += 4;
				} else if (info.FieldType.ToLower() == "int64" || info.FieldType.ToLower() == "uint64") {
					CheckWriteAlignmentBy (offset, 8, false);
					WriteLine ("\t" + info.FieldType + StuctFieldsSpacing + info.FieldName + "; // offset = " + offset.Offset);
					offset.Offset += 8;
				}
				else if(info.FieldType.ToLower() == "string" ) {
					if (info.FieldName == "Symbol") {
						CheckWriteAlignmentBy (offset, 16, false);
						WriteLine ("\t" + "char" + StuctFieldsSpacing + info.FieldName + "[16] __attribute__((aligned(16))); // offset = " + offset.Offset);
						offset.Offset += 16;
						WriteLine ("\t" + "int\t" + StuctFieldsSpacing + info.FieldName + "Length; // offset = " + offset.Offset);
						offset.Offset += 4;
					} else if (info.FieldName == "TradingSessionID") {
						WriteLine ("\t" + "char" + StuctFieldsSpacing + info.FieldName + "[4]; // offset = " + offset.Offset);
						offset.Offset += 4;
					}
				}
			}
			CheckWriteAlignmentBy (offset, 16, false);
			WriteLine("\t" + Prefix + "SnapshotInfo() {");
			WriteLine("\t\tmemset(this, 0, sizeof(" + Prefix + "SnapshotInfo));");
			WriteLine("\t}");
			WriteLine("};");

			WriteLine("");
		}

		private void WriteObjectsAllocationInfo() {
			WriteLine("class " + Prefix + "ObjectsAllocationInfo {");
			foreach(StructureInfo info in Structures) {
				WriteLine("\tAutoAllocatePointerList<" + info.Name + ">" + "\t\t\t\t*" + info.ValueName + ";");
			}
			WriteLine("public:");
			WriteLine("\t static " + Prefix + "ObjectsAllocationInfo *Default;");
			WriteLine("\t" + Prefix + "ObjectsAllocationInfo(int count) {");
			foreach(StructureInfo info in Structures) {
				WriteLine("\t\tthis->" + info.ValueName + " = new AutoAllocatePointerList<" + info.Name + ">(count, count, \"" + info.Name + "\");");
			}
			WriteLine("\t}");
			foreach(StructureInfo info in Structures) {
				WriteLine("\tinline void " + info.AllocatePoolMethodName + "(int count, int addCount) {");
				WriteLine("\t\tthis->" + info.ValueName + "->Append(count);");
				WriteLine("\t\tthis->" + info.ValueName + "->AddCount(addCount);");
				WriteLine("\t}");
			}
			foreach(StructureInfo info in Structures) {
				WriteLine("\tinline void " + info.AllocatePoolMethodName + "To(int count) {");
				WriteLine("\t\tcount -= this->" + info.ValueName + "->Capacity();");
				WriteLine("\t\tif(count > 0)");
				WriteLine("\t\t\tthis->" + info.ValueName + "->Append(count);");
				WriteLine("\t}");
			}
			foreach(StructureInfo info in Structures) {
				WriteLine("\tinline AutoAllocatePointerList<" + info.Name + ">* " + info.GetListMethodName + "() {");
				WriteLine("\t\treturn this->" + info.ValueName + ";");
				WriteLine("\t}");
			}
			WriteLine("};");
		}

		private void WritePresenceIndexClasses(List<StructureInfo> structures) {
			foreach(StructureInfo info in structures) {
				bool hasPresenceIndex = false;
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteCheckPresenceMapCode(field))
						continue;
					hasPresenceIndex = true;
					break;
				}
				if(!hasPresenceIndex)
					continue;
				WriteLine("class " + info.PresenceIndicesClassName + "{");
				WriteLine("public:");
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteCheckPresenceMapCode(field))
						continue;
					WriteLine("\tstatic const UINT64 " + Name(field) + "PresenceIndex = PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(field) + ";");
				}
				WriteLine("};");
			}
		}

		private uint PackTemplateId(uint value) {
			uint encoded = 0;

			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0)
				return encoded;

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0)
				return encoded;

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0)
				return encoded;

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0)
				return encoded;
			
			throw new NotImplementedException ();
		}

		private string GetPacketTemplateIdString(int value) {
			uint packetValue = PackTemplateId ((uint)value);
			return string.Format ("0x{0:x4}", packetValue);
		}

		private void WriteTemplateIdClasses(List<StructureInfo> structures) {
			WriteLine("class " + Prefix + "PackedTemplateId {");
			WriteLine ("public:");
			foreach (StructureInfo info in structures) {
				if (info.IsSequence)
					continue;
				WriteLine ("\tstatic const UINT32 " + info.Name + " = " + GetPacketTemplateIdString(info.TemplateId) + ";");
			}
			WriteLine ("};");

		}

		private void WriteNullIndexClasses(List<StructureInfo> structures) {
			foreach(StructureInfo info in structures) {
				bool hasNullableIndex = false;
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteNullCheckCode(field))
						continue;
					hasNullableIndex = true;
					break;
				}
				if(!hasNullableIndex)
					continue;
				WriteLine("class " + info.NullIndicesClassName + "{");
				WriteLine("public:");
				foreach(XmlNode field in info.Fields) {
					if(!ShouldWriteNullCheckCode(field))
						continue;
					WriteLine("\tstatic const UINT64 " + Name(field) + "NullIndex = NULL_MAP_INDEX" + CalcNullIndex(field) + ";");
				}
				WriteLine("};");
			}
		}

		private  void WriteStructuresDefinitionCode (XmlNode templatesNode, bool writeSnapshotInfoCode) {
			ClearRegion(Message_Info_Structures_Definition_GeneratedCode);
			SetPosition(Message_Info_Structures_Definition_GeneratedCode);
			if(writeSnapshotInfoCode)
				WriteSnapshotInfoDefinitionCode(templatesNode);

			foreach(StructureInfo info in Structures) { 
				WriteLine("class " + info.Name + ";");
			}
			WriteLine("");
			foreach(StructureInfo info in Structures) { 
				WriteStructureDefinition(info);
			}

			List<StructureInfo> structures = GetStructures(templatesNode);
			WriteObjectsAllocationInfo();
			WritePresenceIndexClasses(structures);
			WriteNullIndexClasses(structures);
			WriteTemplateIdClasses(structures);
		}

		int GetMaxSize(XmlNode field) {
			return HasAttribute(field, "size") ? int.Parse(field.Attributes["size"].Value) : 0;
		}

		int GetMaxStringSize(XmlNode field) {
			int maxStringLength = GetMaxSize(field);
			if(maxStringLength == 0) {
				maxStringLength = 16;
				string name = Name(field);
				if(name == "Text")
					maxStringLength = 512;
				if(name == "TargetCompID" || name == "SenderCompID")
					maxStringLength = 32;
				if(name == "MDEntryType")
					maxStringLength = 4;
				if(name == "MDEntryTradeType")
					maxStringLength = 4;
				if(name == "Currency")
					maxStringLength = 4;
				if(name == "OpenCloseSettlFlag")
					maxStringLength = 4;
				if(name == "OrdType")
					maxStringLength = 4;
				if(name == "SettlType")
					maxStringLength = 4;
				if(name == "OrderSide")
					maxStringLength = 4;
				if(name == "OrderStatus")
					maxStringLength = 4;
				if(name == "CXFlag")
					maxStringLength = 4;
				if(name == "TradingSessionSubID")
					maxStringLength = 4;
			}
			return maxStringLength;
		}

		string GetUnionType(XmlNode field) {
			if(field.Attributes["union"].Value == "uint32")
				return "UINT32";
			throw new ArgumentException("union");
		}
		string GetTypeSuffix(XmlNode field) {
			if(field.Attributes["union"].Value == "uint32")
				return "Uint";
			throw new ArgumentException("union");
		}

		public int GetDefaultOrderIndex(XmlNode field) {
			if (field.NodeType == XmlNodeType.Comment)
				return 0;
			string name = Name (field);
			if (name == "MessageType" ||
				name == "ApplVerID" ||
				name == "BeginString" ||
				name == "SenderCompID" ||
				name == "MsgSeqNum" ||
				name == "SendingTime" || 
				name == "MessageType")
				return 999; // write last
			return 0;
		}
		public int GetOrderIndex(XmlNode node) { 
			if (!HasAttribute (node, "order"))
				return GetDefaultOrderIndex (node);
			return Convert.ToInt32 (node.Attributes ["order"].Value);
		}

		void WriteStringDefinitionCore(XmlNode field, string tabs, int offset) {
			int maxStringLength = GetMaxStringSize(field);
			if (HasAttribute (field, "union")) {
				WriteLine ("\tunion {");
				if (HasAttribute (field, "aligned"))
					WriteLine ("\t\tchar\t\t" + Name (field) + "[" + maxStringLength + "] __attribute__((aligned(" + field.Attributes ["aligned"].Value + ")));" + GetCommentLine (field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
				else
					WriteLine ("\t\tchar\t\t" + Name (field) + "[" + maxStringLength + "];" + GetCommentLine (field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
				WriteLine ("\t\t" + GetUnionType (field) + "\t\t" + Name (field) + GetTypeSuffix (field) + ";");
				WriteLine ("\t};");
			} else {
				if (HasAttribute (field, "aligned"))
					WriteLine ("\tchar" + tabs + Name (field) + "[" + maxStringLength + "] __attribute__((aligned(" + field.Attributes ["aligned"].Value + ")));" + GetCommentLine (field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
				else
					WriteLine ("\tchar" + tabs + Name (field) + "[" + maxStringLength + "];" + GetCommentLine (field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
			}
		}

		int GetMaxByteVectorSize(XmlNode field) {
			int maxStringLength = GetMaxSize(field);
			if(maxStringLength == 0) {
				maxStringLength = 128;
				//string name = Name(field);
				/*
				if(name == "Text")
					maxStringLength = 512;
				if(name == "TargetCompID" || name == "SenderCompID")
					maxStringLength = 32;
				if(name == "MDEntryType")
					maxStringLength = 4;
				if(name == "OpenCloseSettlFlag")
					maxStringLength = 4;
				if(name == "OrdType")
					maxStringLength = 4;
				if(name == "SettlType")
					maxStringLength = 4;
				if(name == "OrderSide")
					maxStringLength = 4;
				if(name == "OrderStatus")
					maxStringLength = 4;
				if(name == "CXFlag")
					maxStringLength = 4;
				if(name == "TradingSessionSubID")
					maxStringLength = 4;
				*/
			}
			return maxStringLength;
		}

		void WriteByteVectorDefinitionCore(XmlNode field, string tabs, int offset) {
			int maxStringLength = GetMaxByteVectorSize(field);
			WriteLine("\tunsigned char" + tabs + Name(field) + "[" + maxStringLength + "];" + GetCommentLine(field) + " offset = " + offset);
		}

		List<StructureInfo> structures;
		protected List<StructureInfo> Structures { 
			get { 
				if(structures == null)
					structures = MergeStructures(GetStructures(TemplatesNode));
				return structures;
			}
		}
		void ClearStructures() { this.structures = null; }

		int CalcMaxTemplateId(XmlNode templatesNode) {
			List<XmlNode> list = GetTemplates(templatesNode);
			int id = 0;
			foreach(XmlNode t in list) {
				int tid = Int32.Parse(t.Attributes["id"].Value);
				id = Math.Max(id, tid);
			}
			return id;
		}

		int CalcMinTemplateId(XmlNode templatesNode) {
			List<XmlNode> list = GetTemplates(templatesNode);
			int id = 100000;
			foreach(XmlNode t in list) {
				int tid = Int32.Parse(t.Attributes["id"].Value);
				id = Math.Min(id, tid);
			}
			return id;
		}

		protected string DecodeMethodsName { get { return "m_" + Prefix.ToLower() + "DecodeMethods"; } }
		protected string ReleaseMethodsName { get { return "m_" + Prefix.ToLower() + "ReleaseMethods"; } }
		protected string GetSnapshotInfoMethodsMethodsName { get { return "m_" + Prefix.ToLower() + "GetSnapshotInfoMethods"; } }

		private  bool SetPosition (string keyword) {
			ManagerHFile.GoTo(0);
			ManagerCppFile.GoTo(0);
			TypesFile.GoTo(0);
			RobotCppFile.GoTo(0);
			int index = ManagerHFile.FindString(keyword);
			if(index >= 0) {
				ManagerHFile.GoTo(index + 1);
				CurrentFile = ManagerHFile;
				return true;
			}
			index = ManagerCppFile.FindString(keyword);
			if(index >= 0) {
				ManagerCppFile.GoTo(index + 1);
				CurrentFile = ManagerCppFile;
				return true;
			}
			index = TypesFile.FindString(keyword);
			if(index >= 0) {
				TypesFile.GoTo(index + 1);
				CurrentFile = TypesFile;
				return true;
			}
			index = RobotCppFile.FindString(keyword);
			if(index >= 0) {
				RobotCppFile.GoTo(index + 1);
				CurrentFile = RobotCppFile;
				return true;
			}

			Console.WriteLine("hfile " + ManagerSourceFileH + " " + ManagerHFile.Lines.Count);
			Console.WriteLine("cppfile " + ManagerSourceFileCpp + " " + ManagerCppFile.Lines.Count);
			Console.WriteLine("types_file " + TypesFile.Lines.Count);
			throw new Exception("error cant find keyword " + keyword);
		}

		class DecodeMessageInfo {
			public DecodeMessageInfo() { 
				Prefix = "Fast";
			}
			public string Prefix { get; set; }
			public string NameCore { get; set; }
			public string MsgType { get; set; }
			public int TemplateId { get; set; }
			public string FullDecodeMethodName { get { return "Decode" + Prefix + NameCore; } }
			public string FullReleaseMethodName { get { return "Release" + Prefix + NameCore + "Info"; } }
			public bool HasGetSnapshotInfoMethod { get; set; } 
			public string FullGetSnapshotInfoMethod { get { return "Get" + Prefix + "SnapshotInfo" + NameCore; } }
			public string PrintMethodName { get { return "Print" + Prefix + NameCore; } }
			public string PrintXmlMethodName { get { return "PrintXml" + Prefix + NameCore; } }
			public string StructName { get { return Prefix + NameCore + "Info"; } }
		}

		int CompareDecodeMessage(DecodeMessageInfo x, DecodeMessageInfo y) {
			if(x.TemplateId == y.TemplateId)
				return 0;
			return x.TemplateId < y.TemplateId? -1: 1;
		}

		void WriteSelector(string tabs, List<DecodeMessageInfo> list, WriteConditionDelegate del) {
			list.Sort(new Comparison<DecodeMessageInfo>(CompareDecodeMessage));
			if(list.Count == 0)
				return;
			if(list.Count == 1) {
				WriteLine (tabs + "if(this->m_templateId == " + list [0].TemplateId + ")");
				del(tabs + "\t", list[0]);
				return;
			}
			int a = 0, b = list.Count - 1, c = (a + b) / 2;
			WriteCondition(tabs, list, a, b, c, del);
		} 
		delegate void WriteConditionDelegate(string tabs, DecodeMessageInfo info);
		void WriteCondition(string tabs, List<DecodeMessageInfo> list, int a, int b, int c, WriteConditionDelegate del) {
			if(b - a == 1) {
				WriteLine(tabs + "if(this->m_templateId == " + list[a].TemplateId + ") {");
				del(tabs + "\t", list[a]);
				WriteLine(tabs + "}");
				WriteLine(tabs + "else { // " + list[b].TemplateId);
				del(tabs + "\t", list[b]);
				WriteLine(tabs + "}");
			} else {
				WriteLine(tabs + "if(this->m_templateId <= " + list[c].TemplateId + ") {");
				WriteCondition(tabs + "\t", list, a, c, (a + c) / 2, del);
				WriteLine(tabs + "}");
				WriteLine(tabs + "else {");
				WriteCondition(tabs + "\t", list, c, b, (c + b) / 2, del);
				WriteLine(tabs + "}");
			}
		}

		private void WriteDecodeMethod(string tabs, DecodeMessageInfo info) {
			WriteLine(tabs + "this->m_lastDecodedInfo = this->" + info.FullDecodeMethodName + "();");
			WriteLine(tabs + "return this->m_lastDecodedInfo;");
		}
		private void WriteGetSnapshotInfoMethod(string tabs, DecodeMessageInfo info) {
			WriteLine(tabs + "return this->" + info.FullGetSnapshotInfoMethod + "();");
		}

		private void WriteReleaseMethod(string tabs, DecodeMessageInfo info) {
			WriteLine(tabs + "this->" + info.FullReleaseMethodName + "();");
		}
		private  void WriteEntireMethodsCode (XmlNode templatesNode) {
			WriteLine("\tinline void* Decode" + Prefix + "() {");
			WriteLine("\t\tthis->Decode" + Prefix + "Header();");
			List<DecodeMessageInfo> messages = GetDecodeMessageMethods(templatesNode);
			WriteSelector("\t\t", GetDecodeMessageMethods(templatesNode), new WriteConditionDelegate(WriteDecodeMethod));
			WriteLine("\t}");

			WriteLine("\tvoid Print" + Prefix + "() {");
			WriteLine("");
			WriteLine("\t\tswitch(this->m_templateId) {");

			foreach(DecodeMessageInfo info in messages) {
				WriteLine("\t\t\tcase " + info.TemplateId + ":");
				WriteLine("\t\t\t\t" + info.PrintMethodName + "(static_cast<" + info.StructName + "*>(this->m_lastDecodedInfo));");
				WriteLine("\t\t\t\tbreak;");
			}
			WriteLine("\t\t}");
			WriteLine("\t}");

			WriteLine("\tvoid PrintXml" + Prefix + "() {");
			WriteLine("");
			WriteLine("\t\tswitch(this->m_templateId) {");
			foreach(DecodeMessageInfo info in messages) {
				WriteLine("\t\t\tcase " + info.TemplateId + ":");
				WriteLine("\t\t\t\t" + info.PrintXmlMethodName + "(static_cast<" + info.StructName + "*>(this->m_lastDecodedInfo));");
				WriteLine("\t\t\t\tbreak;");
			}
			WriteLine("\t\t}");
			WriteLine("\t}");

			WriteLine("\tinline " + Prefix + "SnapshotInfo* Get" + Prefix + "SnapshotInfo() {");
			WriteLine("\t\tthis->Decode" + Prefix + "Header();");
			WriteSelector("\t\t", GetSnapshotMessageMethods(templatesNode), new WriteConditionDelegate(WriteGetSnapshotInfoMethod));
			WriteLine("\t\treturn this->Get" + Prefix + "SnapshotInfoUnsupported();");
			WriteLine("\t}");
		}

		bool IsSnapshotMessage(XmlNode node) {
			if(Mode == GeneratorMode.Asts) 
				return node.PreviousSibling.Value.Contains("Snapshot");
			return node.Attributes["name"].Value.Contains("Snapshot");
		}

		private  List<DecodeMessageInfo> GetSnapshotMessageMethods (XmlNode templatesNode) {
			List<DecodeMessageInfo> src = GetDecodeMessageMethods(templatesNode);
			List<DecodeMessageInfo> res = new List<DecodeMessageInfo>();
			foreach(DecodeMessageInfo info in src) {
				if(info.HasGetSnapshotInfoMethod)
					res.Add(info);
			}
			return res;
		}

		DecodeMessageInfo GetDecodeMessageInfo(XmlNode node) {
			DecodeMessageInfo info = new DecodeMessageInfo();
			info.Prefix = Prefix;
			if(node.Attributes == null)
				throw new ArgumentException("Attributes == null for node" + node.Value.ToString());
			info.MsgType = node.Attributes["name"].Value.Substring(0, 1);
			info.TemplateId = Int32.Parse(node.Attributes["id"].Value);
			info.NameCore = GetTemplateName(node);
			info.HasGetSnapshotInfoMethod = IsSnapshotMessage(node);
			return info;
		}

		private  List<DecodeMessageInfo> GetDecodeMessageMethods (XmlNode templatesNode) {
			List<DecodeMessageInfo> res = new List<DecodeMessageInfo>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				DecodeMessageInfo info = GetDecodeMessageInfo(node);
				res.Add(info);
			}
			return res;
		}

		string GetMethodSuffix (XmlNode node) {
			if(!node.Attributes["name"].Value.Contains('-'))
				return string.Empty;
			return node.Attributes["name"].Value.Substring(node.Attributes["name"].Value.IndexOf('-')).Replace('-', '_');
		}

		private  List<string> GetDecodeEntryMethodList (XmlNode templatesNode) {
			List<string> res = new List<string>();
			foreach(XmlNode node in templatesNode.ChildNodes) {
				if(node.Name != "template")
					continue;
				if(node.Attributes["name"].Value.Contains('-')) {
					string name = GetMethodSuffix(node);
					if(!res.Contains(name))
						res.Add(name);
				}
			}
			return res;
		}

		private void WritePointerCode(StructureInfo info) {
			WriteLine("\tLinkedPointer<" + info.Name + ">" + StuctFieldsSpacing + "*Pointer;");
			WriteLine("\tAutoAllocatePointerList<" + info.Name + ">" + StuctFieldsSpacing + "*Allocator;");
		}

		List<XmlNode> SortNodesByPriority(StructureInfo info) {
			return info.Fields.OrderBy (n => GetOrderIndex (n)).ToList ();
		}

		void WritePaddingBytes(int index, int count) {
			WriteLine ("\tchar" + StuctFieldsSpacing + "PaddingBytes" + index + "[" + count + "];");
		}

		bool IsAligned(int offset, int alignBytes) {
			return (offset % alignBytes) == 0;
		}

		int CalcPaddingBytes(int offset, int alignBytes) {
			return alignBytes - (offset % alignBytes);
		}

		class StructureFieldOffsetInfo { 
			public int Offset { get; set; }
			public int PaddingIndex { get; set; }
		}

		void CheckWriteAlignmentBy(StructureFieldOffsetInfo info, int align, bool onlyCalculate) {
			if (!IsAligned (info.Offset, align)) {
				int paddingBytes = CalcPaddingBytes (info.Offset, align);
				if (paddingBytes == 0)
					return;
				if(!onlyCalculate)
					WritePaddingBytes (info.PaddingIndex, paddingBytes);
				info.Offset += paddingBytes;
				info.PaddingIndex++;
			}
		}

		int GetUnionSize(XmlNode field) {
			string unionName = field.Attributes ["union"].Value;
			if (unionName.Contains ("32"))
				return 4;
			if (unionName.Contains ("64"))
				return 8;
			return 1;
		}

		List<XmlNode> RemoveUnusedFields(List<XmlNode> list) {
			return list.Where((f) => (!HasAttribute(f, "remove")) && (f.NodeType != XmlNodeType.Comment)).ToList();
		}

		private  int WriteStructureFieldsDefinitionCode (StructureInfo info, string parentName) {
			return WriteStructureFieldsDefinitionCode (info, parentName, false);
		}
		private  int WriteStructureFieldsDefinitionCode (StructureInfo info, string parentName, bool onlyCalculateSize) {
			StructureFieldOffsetInfo offset = new StructureFieldOffsetInfo ();
			offset.Offset = 0;

			List<XmlNode> sortedFields = SortNodesByPriority (info);
			sortedFields = RemoveUnusedFields (sortedFields);
			foreach (XmlNode field in sortedFields) {
				if (field.Name == "sequence") {
					CheckWriteAlignmentBy (offset, 4, onlyCalculateSize);
					WriteCount (field, offset.Offset);
					offset.Offset += 4;
					CheckWriteAlignmentBy (offset, 8, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteSequence (field, parentName, offset.Offset);
					offset.Offset += 8 * GetSequenceMaxCount(field);
				} else if (field.Name == "decimal") {
					CheckWriteAlignmentBy (offset, 8, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteDecimalField (field, offset.Offset);
					offset.Offset += 8 + 8;
				} else if (field.Name == "uInt64") {
					CheckWriteAlignmentBy (offset, 8, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteUint64Field (field, offset.Offset);
					offset.Offset += 8;
				} else if (field.Name == "int64") {
					CheckWriteAlignmentBy (offset, 8, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteInt64Field (field, offset.Offset);
					offset.Offset += 8;
				} else if (field.Name == "uInt32") {
					CheckWriteAlignmentBy (offset, 4, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteUint32Field (field, offset.Offset);
					offset.Offset += 4;
				} else if (field.Name == "int32") {
					CheckWriteAlignmentBy (offset, 4, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteInt32Field (field, offset.Offset);
					offset.Offset += 4;
				} else if (IsString (field)) {
					if (!HasAttribute (field, "fixed_size")) {
						// write size
						CheckWriteAlignmentBy (offset, 4, onlyCalculateSize);
						if(!onlyCalculateSize)
							WriteLength (field, offset.Offset);
						offset.Offset += 4;
					}
					if (HasAttribute (field, "aligned"))
						CheckWriteAlignmentBy (offset, Convert.ToInt32 (field.Attributes ["aligned"].Value), onlyCalculateSize);
					else if(HasAttribute(field, "union"))
						CheckWriteAlignmentBy (offset, GetUnionSize(field), onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteStringDefinition (field, offset.Offset);
					offset.Offset += GetMaxStringSize (field);
				} else if (IsByteVector (field)) {
					CheckWriteAlignmentBy (offset, 4, onlyCalculateSize);
					if(!onlyCalculateSize)
						WriteLength (field, offset.Offset);
					offset.Offset += 4;
					if(!onlyCalculateSize)
						WriteByteVectorField (field, offset.Offset);
					offset.Offset += GetMaxStringSize (field);
				}
			}
			CheckWriteAlignmentBy (offset, 8, onlyCalculateSize);
			if (onlyCalculateSize)
				return offset.Offset;
			WritePresenceMapDefinition();
			WriteNullMapDefinition();
			WritePointerCode(info);
			offset.Offset += 8 + 8 + 8 + 8;
			CheckWriteAlignmentBy (offset, 16, onlyCalculateSize);
			WriteLine("");
			WriteLine("\t" + info.Name + "() {");
			WriteLine ("\t\tmemset(this, 0, sizeof(" + info.Name + "));");
			WriteLine("\t}");
			WriteLine("\t~" + info.Name + "() { }");

			WriteAssignCode(info);
			WriteClearCode(info);
			return offset.Offset;
		}

		private void WriteClearFieldsCode(StructureInfo info) {
			WriteLine("\t\tthis->PresenceMap = 0;");
			WriteLine("\t\tthis->NullMap = 0;");
			foreach(XmlNode field in info.Fields) {
				if(IsString(field))
					WriteClearStringCode(field);
				if(field.Name == "sequence")
					WriteLine("\t\tthis->" + Name(field) + "Count = 0;");
			}
		}

		private void WriteClearStringCode(XmlNode field) {
			WriteLine("\t\tthis->" + Name(field) + "[0] = '\\0';");
			WriteLine("\t\tthis->" + Name(field) + "Length = 0;");
		}

		int CalcStructureSize(StructureInfo info) {
			return WriteStructureFieldsDefinitionCode (info, "", true);
		}

		private void WriteAssignCode(StructureInfo info) { 
			WriteLine ("\tinline void Assign(" + info.Name + " *item) {");
			int size = CalcStructureSize(info);
			WriteLine ("\t\t// size = " + size);
			int count = size / 16;
			if (size % 16 != 0)
				count++;
			WriteLine ("\t\t__m128 *dst = (__m128*)this;");
			WriteLine ("\t\t__m128 *src = (__m128*)item;");
			WriteLine ("\t\tfor(int i = 0; i < " + count + "; i++, src ++, dst ++) {");
				WriteLine ("\t\t\t__m128 t = *src;");
				WriteLine ("\t\t\t*(dst) = t;");
			WriteLine ("\t\t}");
			WriteLine("\t}");
		}

		private void WriteClearCode(StructureInfo info) {
			WriteLine("\tinline void Clear() {");

			if (!info.AllowCache) {
				WriteLine ("\t\tthis->Allocator->FreeItemUnsafe(this->Pointer);");
			}
			foreach(XmlNode field in info.Fields) {
				if(field.Name != "sequence")
					continue;
				WriteLine("\t\tfor(int i = 0; i < this->" + Name(field) + "Count; i++)");
				WriteLine("\t\t\tthis->" + Name(field) + "[i]->Clear();");
			}
			WriteLine("\t}");			

			WriteLine("\tinline void ReleaseUnused() {");
			WriteLine("");
			if(!info.AllowCache)
				WriteLine("\t\tthis->Allocator->FreeItemUnsafe(this->Pointer);");
			foreach(XmlNode field in info.Fields) {
				if(field.Name != "sequence")
					continue;
				WriteLine("\t\tfor(int i = 0; i < this->" + Name(field) + "Count; i++)");
				WriteLine("\t\t\tthis->" + Name(field) + "[i]->ReleaseUnused();");
			}
			WriteLine("\t}");	

			WriteLine("\tinline void ReleaseUnusedChildren() {");
			foreach(XmlNode field in info.Fields) {
				if(field.Name != "sequence")
					continue;
				WriteLine("\t\tfor(int i = 0; i < this->" + Name(field) + "Count; i++)");
				WriteLine("\t\t\tthis->" + Name(field) + "[i]->ReleaseUnused();");
			}
			WriteLine("\t}");
		}

		string StuctFieldsSpacing { get{ return "\t\t\t\t\t\t\t"; } }

		private  void WritePresenceMapDefinition () {
			WriteLine("\tUINT64" + StuctFieldsSpacing + "PresenceMap;");
		}

		private  void WriteNullMapDefinition () {
			WriteLine("\tUINT64" + StuctFieldsSpacing + "NullMap;");
		}

		int CalcPresenceMapByteCount(XmlNode node) {
			int maxPresenceBitCount = GetMaxPresenceBitCount(node);
			return CalcPresenceMapByteCount(maxPresenceBitCount);
		}

		int CalcPresenceMapIntCount(XmlNode node) {
			int maxPresenceBitCount = GetMaxPresenceBitCount(node);
			return CalcPresenceMapIntCount(maxPresenceBitCount);
		}

		int CalcPresenceMapIntCount(int bitCount) {
			int res = CalcPresenceMapByteCount(bitCount);
			int intRes = res / 4;
			if(res % 4 > 0)
				intRes++;
			if(intRes == 0)
				return 1;
			return intRes;
		}

		int CalcPresenceMapByteCount(int bitCount) {
			int res = bitCount / 7;
			if(bitCount % 7 > 0)
				res++;
			return res;
		}

		bool FieldMandatoryAndHasConstant (XmlNode field) {
			if(field.ChildNodes.Count == 1 && field.ChildNodes[0].Name == "constant")
				return true;
			return false;
		}

		string GetFieldConstantValue (XmlNode field) { 
			if(!FieldMandatoryAndHasConstant(field))
				return string.Empty;
			return field.ChildNodes[0].Attributes["value"].Value;
		}

		string GetCommentLine (XmlNode field) {
			string result = string.Empty;

			foreach(XmlAttribute attribute in field.Attributes) { 
				if(attribute.Name == "name")
					continue;
				if(!IsKnownAttribute(attribute))
					Console.WriteLine("\nERROR: unknown attribute " + attribute.Name);
				result += attribute.Name + "=" + attribute.Value + "  ";
			}
			if(field.Name != "sequence") {
				foreach(XmlNode child in field.ChildNodes) { 
					result += "  " + child.Name + (child.Value != null ? "=" + child.Value.ToString() : "");
				}
			}
			if(FieldMandatoryAndHasConstant(field))
				result += " has constant value = " + GetFieldConstantValue(field);
			return string.IsNullOrEmpty(result) ? result : "\t\t\t// " + result;
		}

		private  bool IsKnownAttribute (XmlAttribute attribute) {
			return attribute.Name == "name" || 
				attribute.Name == "id" || 
				attribute.Name == "presence" || 
				attribute.Name == "charset" || 
				attribute.Name == "fixed_size" || 
				attribute.Name == "size" || 
				attribute.Name == "predict" || 
				attribute.Name == "union" ||
				attribute.Name == "skip" || 
				attribute.Name == "remove" ||
				attribute.Name == "aligned" || 
				attribute.Name == "order" || 
				attribute.Name == "max_count" || 
				attribute.Name == "process_empty_pmap" || 
				attribute.Name == "pmap1" || 
				attribute.Name == "pmap2" || 
				attribute.Name == "pmap3";
		}
		StructureInfo GetOriginalStruct(XmlNode field) {
			if(field.ParentNode == null || field.ParentNode.Attributes["name"] == null)
				return null;
			//Console.WriteLine("Get original struct for " + field.ParentNode.Attributes["name"].Value);
			foreach(StructureInfo info in Structures) {
				if(info.HasIncrementalStruct(field))
					return info;
			}
			return null;
		}
		StructureInfo GetStruct(XmlNode field) {
			foreach(StructureInfo info in Structures) {
				if(info.Node == field)
					return info;
			}
			return null;
		}

		int GetSequenceMaxCount(XmlNode field) {
			if (HasAttribute (field, "max_count"))
				return Convert.ToInt32 (field.Attributes ["max_count"].Value);
			return 256;
		}
		private  void WriteSequence (XmlNode field, string parentName, int offset) {
			StructureInfo originalStruct = GetOriginalStruct(field);
			int count = GetSequenceMaxCount(field);
			if(originalStruct != null) {
				originalStruct.Prefix = Prefix;
				WriteLine("\t" + originalStruct.Name + "* " + Name(field) + "[" + count + "];" + GetCommentLine(field) + "//\t\t offset = " + offset + " order =  " + GetOrderIndex(field));
			}
			else
				WriteLine("\t" + Prefix + parentName + ItemName(field) + "ItemInfo* " + Name(field) + "[" + count + "];" + GetCommentLine(field) + "//\t\t offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private  void WriteByteVectorField (XmlNode field, int offset) {
			WriteByteVectorDefinitionCore(field, StuctFieldsSpacing, offset);
		}

		private  void WriteDecimalField (XmlNode field, int offset) {
			WriteLine("\tDecimal" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private  void WriteInt64Field (XmlNode field, int offset) {
			WriteLine("\tUINT64" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private  void WriteUint64Field (XmlNode field, int offset) {
			WriteLine("\tUINT64" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private  void WriteInt32Field (XmlNode field, int offset) {
			WriteLine("\tINT32" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private  void WriteUint32Field (XmlNode field, int offset) {
			WriteLine("\tUINT32" + StuctFieldsSpacing + Name(field) + ";" + GetCommentLine(field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private  void WriteStringDefinition (XmlNode field, int offset) {
			WriteStringDefinitionCore(field, StuctFieldsSpacing, offset);
		}

		private void WriteLength(XmlNode field, int offset) {
			if (HasAttribute (field, "fixed_size"))
				return;
			WriteLine("\tint\t"+ StuctFieldsSpacing + Name(field) + "Length;" + GetCommentLine(field) + " offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		private void WriteCount(XmlNode field, int offset) {
			WriteLine("\tint\t" + StuctFieldsSpacing + Name(field) + "Count;" + "//\t\t offset = " + offset + " order =  " + GetOrderIndex(field));
		}

		string GetTemplateName(XmlNode node) {
			if(Mode == GeneratorMode.Asts)
				return GetTemplateNameAsts(node.PreviousSibling.Value);
			return node.Attributes["name"].Value.ToString();
		}

		string GetTemplateNameAsts (string templateName) {
			templateName = templateName.Replace("-", "");
			templateName = templateName.Replace("/", "");
			templateName = templateName.Replace(" ", "");
			templateName = templateName.Replace("Full", "");
			templateName = templateName.Replace("Market", "");
			templateName = templateName.Replace("Data", "");
			templateName = templateName.Replace("Snapshot", "");
			templateName = templateName.Replace("Refresh", "");
			return templateName;
		}

		private  void WriteStructureDefinition (StructureInfo info) { 
			WriteLine("class " + info.Name + "{");
			WriteLine("public:");
			WriteStructureFieldsDefinitionCode(info, info.NameCore);
			WriteLine("};");
			WriteLine("");
		}

		void WriteParsePresenceMap (XmlNode node, string info, string tabString) {
			int byteCount = CalcPresenceMapByteCount (node);
			WriteLine(tabString + "UINT64 pmap" + LevelCount + " = this->ParsePresenceMap" + byteCount + "();");
		}

		private  int GetMaxPresenceBitCount (XmlNode node) {
			int count = 0;
			foreach (XmlNode field in node.ChildNodes) {
				//Console.WriteLine (Name (field) + " presence = " + ShouldWriteCheckPresenceMapCode (field))/;
				if (ShouldWriteCheckPresenceMapCode (field)) {
					count++;
				}
			}
			//Console.WriteLine("calc presence map for " + Name(node) + " = " + count);
			return count;
		}

		bool IsValueBelongsToHeader(XmlNode value) {
			if(value.Attributes["id"] == null)
				return false;
			return HeaderTags.Contains(value.Attributes["id"].Value);
		}

		private void WriteCopyPresenceMap(string tabs, string infoName) {
			WriteLine(tabs + infoName + "->PresenceMap = this->m_presenceMap;");
		}

		private  void ParseTemplateNode(XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { Node = template, NameCore = templateName };
			info.Prefix = Prefix;
			WriteLine("\tinline " + info.Name + "* Decode" + Prefix + templateName + "() {");
			info.Prefix = Prefix;
			WriteLine("\t\t" + Prefix + templateName + "Info* info = " + info.GetFreeMethodName + "();");
			if(GetMaxPresenceBitCount(template) != 0)
				WriteLine ("\t\tUINT64 pmap" + LevelCount + " = this->m_presenceMap;");

			WriteLine ("\t\tUINT64 nmap" + LevelCount + " = 0;");
			WriteLine("");
			foreach(XmlNode value in template.ChildNodes) {
				ParseValue(info, value, "info", templateName, "\t\t", false, false, 0);
			}
			if(GetMaxPresenceBitCount(template) != 0)
				WriteCopyPresenceMap("\t\t", "info");
			WriteLine ("\t\tinfo->NullMap = nmap" + LevelCount + ";");
			WriteLine("\t\tthis->" + info.PrevValueName + " = info;");
			WriteLine("\t\treturn info;");
			WriteLine("\t}");
		}

		public class SnapshotFieldInfo { 
			public SnapshotFieldInfo(string fieldType, string fieldName) {
				FieldType = fieldType;
				FieldName = fieldName;
			}
			public string FieldType { get; set; }
			public string FieldName { get; set; }
		}
		protected List<SnapshotFieldInfo> SnapshotInfoFields { 
			get;
			set;
		}

		private XmlNode GetChildNode(XmlNode root, string childName) {
			foreach(XmlNode node in root.ChildNodes) {
				if(node.NodeType == XmlNodeType.Comment)
					continue;
				if(node.Attributes["name"].Value == childName)
					return node;
			}
			return null;
		} 

		private void InitializeSnapshotInfoFields(XmlNode templates) {
			List<XmlNode> nodes = GetTemplates(templates);
			foreach(SnapshotFieldInfo info in SnapshotInfoFields) {
				foreach(XmlNode node in nodes) {
					XmlNode child = GetChildNode(node, info.FieldName);
					if(child != null) {
						info.FieldType = child.Name.ToUpper();
						break;
					}
				}
			}
		}

		private bool IsSnapshotNode(XmlNode node) {
			foreach(SnapshotFieldInfo field in SnapshotInfoFields) {
				if(field.FieldName == node.Attributes["name"].Value)
					return true;
			}
			return false;
		}

		private bool HasSnapshotFields(XmlNode template) {
			foreach(XmlNode node in template.ChildNodes) {
				if(IsSnapshotNode(node))
					return true;
			}
			return false;
		}

		private bool HasField(XmlNode template, string name) {
			foreach(XmlNode node in template.ChildNodes) {
				if(node.NodeType == XmlNodeType.Comment)
					continue;
				if(node.Attributes["name"].Value == name)
					return true;
			}
			return false;
		}

		private void WriteGetTotNumReportsMethod(XmlNode template) {
			bool found = false;
			string templateName = "";
			foreach(XmlNode node in template.ChildNodes) {
				if(node.NodeType == XmlNodeType.Comment)
					continue;
				if(node.Name != "template")
					continue;
				templateName = GetTemplateName(node);
				if(templateName.Contains("SecurityDefinition")) {
					found = true;
					template = node;
					break;
				}
			}

			if(!found) {
				throw new Exception("Symbol Template not found");
			}

			WriteLine("\tint Get" + Prefix + "TotalNumReports() {");
			if(!HasField(template, "TotNumReports"))
				throw new Exception("There is no TotNumReports field in " + templateName + " template");
			WriteLine("\t\t// ReadMsgNumber and DecodeHeader should be called first");
			foreach(XmlNode value in template.ChildNodes) {
				if(value.NodeType == XmlNodeType.Comment)
					continue;
				string name = Name(value);
				if(value.Name == "sequence") {
					throw new Exception("Sequence exceeded. TotNumReports not found");
				}
				if(!CanParseValue(value))
					continue;
				if(name != "TotNumReports") {
					WriteSkipCode("\t\t", name);
					continue;
				}
				if (UseBmi) {
					if (HasOptionalPresence (value))
						WriteLine ("\t\treturn ReadInt32_Optional_BMI();");
					else
						WriteLine ("\t\treturn ReadInt32_Mandatory_BMI();");
				} else {
					if (HasOptionalPresence (value))
						WriteLine ("\t\treturn ReadInt32_Optional_Simple();");
					else
						WriteLine ("\t\treturn ReadInt32_Mandatory_Simple();");
				}
				break;
			}
			WriteLine("\t}");
		}

		private  void WriteGetSnapshotInfoMethod(XmlNode template, string templateName) {
			DecodeMessageInfo mi = GetDecodeMessageInfo(template);
			if(!mi.HasGetSnapshotInfoMethod)
				return;
			List<string> parsed = new List<string>();

			WriteLine("\tinline " + Prefix + "SnapshotInfo* Get" + Prefix + "SnapshotInfo" + templateName + "() {");

			if(!HasSnapshotFields(template)) {
				WriteLine("\t\treturn NULL;");
				WriteLine("\t}");
				return;
			}

			WriteLine("\t\t" + Prefix + "SnapshotInfo *info = GetFree" + Prefix + "SnapshotInfo();" );
			WriteCopyPresenceMap("\t\t", "info");
			WriteLine ("\t\tUINT64 nmap" + LevelCount + " = 0;");
			WriteLine("\t\tinfo->TemplateId = this->m_templateId;");
			WriteLine("");
			StructureInfo info = new StructureInfo() { Node = template, NameCore = templateName }; 
			info.Prefix = Prefix;
			foreach(XmlNode value in template.ChildNodes) {
				ParseValue(info, value, "info", templateName, "\t\t", true, SnapshotInfoFields, parsed, false, false, 0);
				if(parsed.Count == SnapshotInfoFields.Count)
					break;
			}
			WriteLine ("\t\tinfo->NullMap = nmap" + LevelCount + ";");
			WriteLine("\t\treturn info;");
			WriteLine("\t}");

			CurrentFile.Line -= 3;
			while(CurrentFile.Lines[CurrentFile.Line].Contains("SkipToNextField")) {
				CurrentFile.Lines.RemoveAt(CurrentFile.Line);
				CurrentFile.Line--;
			}
			CurrentFile.Line += 3;
		}

		private void WritePrintPresenceMap(XmlNode template, string info, string tabs, int tabsCount) {
			if(GetMaxPresenceBitCount(template) > 0) {
				WriteLine(tabs + "PrintPresenceMap(" + info + "->PresenceMap, " + GetMaxPresenceBitCount(template) + ", " + tabsCount + ");");
			}
		}

		private void WritePrintXmlPresenceMap(XmlNode template, string info, string tabs) {
			if(GetMaxPresenceBitCount(template) > 0) {
				WriteLine(tabs + "PrintXmlPresenceMap(" + info + "->PresenceMap, " + GetMaxPresenceBitCount(template) + ");");
			}
		}

		private void PrintDeclareTemplateNode(XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			info.Prefix = Prefix;
			WriteLine("\tvoid Print" + Prefix + templateName + "(" + info.Name + " *info);");
		}
		private void PrintXmlDeclareTemplateNode(XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			info.Prefix = Prefix;
			WriteLine("\tvoid PrintXml" + Prefix + templateName + "(" + info.Name + " *info);");
		}

		private  void PrintTemplateNode (XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			info.Prefix = Prefix;
			WriteLine("void FastProtocolManager::Print" + Prefix + templateName + "(" + info.Name + " *info) {");
			WriteLine("");
			WriteLine("\tprintf(\"" + info.Name + " {\\n\");");
			WritePrintPresenceMap(template, "info", "\t", 1);
			WriteLine("\tPrintInt32(\"TemplateId\", " + template.Attributes["id"].Value + ", 1);");
			foreach(XmlNode value in template.ChildNodes) {
				if(value.NodeType == XmlNodeType.Comment)
					continue;
				PrintValue(value, "info", templateName, "\t", 1);
			}
			WriteLine("\tprintf(\"}\\n\");");
			WriteLine("}");
		}

		private  void PrintXmlTemplateNode (XmlNode template, string templateName) {
			StructureInfo info = new StructureInfo() { NameCore = templateName };
			info.Prefix = Prefix;
			WriteLine("void FastProtocolManager::PrintXml" + Prefix + templateName + "(" + info.Name + " *info) {");
			WriteLine("");
			WriteLine("\tPrintXmlItemBegin(\"" + info.Name +"\");");
			WritePrintXmlPresenceMap(template, "info", "\t");
			WriteLine("\tPrintXmlInt32(\"TemplateId\", " + template.Attributes["id"].Value + ");");
			foreach(XmlNode value in template.ChildNodes) {
				if(value.NodeType == XmlNodeType.Comment)
					continue;
				PrintXmlValue(value, "info", templateName, "\t");
			}
			WriteLine("\tPrintXmlItemEnd(\"" + info.Name +"\");");
			WriteLine("}");
		}

		bool HasAttribute(XmlNode node, string attributeName, string value) {
			return HasAttribute (node, attributeName) && node.Attributes [attributeName].Value == value;
		}

		bool HasAttribute (XmlNode node, string attributeName) {
			if (node.NodeType == XmlNodeType.Comment)
				return false;
			foreach(XmlAttribute attr in node.Attributes)
				if(attr.Name == attributeName)
					return true;
			if(node.Name == "sequence")
				return false;
			foreach(XmlNode child in node.ChildNodes) {
				if(child.Name == attributeName)
					return true;
			}
			return false;
		}

		private  void WriteCheckingPresenceMapCode (XmlNode value, string objectValueName, string classCoreName, string tabString) {
			int fieldPresenceIndex = CalcFieldPresenceIndex(value);
			if(HasOptionalPresence(value)) {
				WriteLine(tabString + "if(CheckOptionalFieldPresence(" + objectValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + fieldPresenceIndex + ")) {");
			} else {
				WriteLine(tabString + "if(CheckMandatoryFieldPresence(" + objectValueName + "->PresenceMap, PRESENCE_MAP_INDEX" + fieldPresenceIndex + ")) {");
			}
		}

		private  void WriteIncrementOpearatorCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "else {");
			WriteLine(tabString + "\t" + structName + "->" + Name(value) + "++;");
			WriteLine(tabString + "}");
		}

		private  bool HasTailAttribute (XmlNode value) {
			return HasChildNode(value, "tail");
		}

		private  bool HasIncrementValueAttribute (XmlNode value) {
			return HasChildNode(value, "increment");
		}

		private  bool HasCopyValueAttribute (XmlNode value) {
			return HasChildNode(value, "copy");
		}

		private  bool HasDefaultValueAttribute (XmlNode value) {
			return HasChildNode(value, "default");
		}

		private  bool HasConstantAttribute (XmlNode value) {
			return HasChildNode(value, "constant");
		}

		private  bool HasOptionalPresence (XmlNode value) {
			return HasAttribute(value, "presence") && value.Attributes["presence"].Value == "optional";
		}

		private  bool HasMandatoryPresence (XmlNode value) {
			return !HasAttribute(value, "presence") || value.Attributes["presence"].Value == "mandatory";
		}

		private  bool HasChildNode (XmlNode value, string name) { 
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == name)
					return true;
			}
			return false;
		}

		private  XmlNode GetHasChildNode (XmlNode value, string name) {
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == name)
					return node;
			}
			return null;
		}

		private  int CalcFieldPresenceIndex (XmlNode value) {
			int index = 0;
			XmlNode parentNode = value.ParentNode;
			foreach(XmlNode node in parentNode.ChildNodes) { 
				if(node == value)
					return index;
				if(ShouldWriteCheckPresenceMapCode(node))
					index++;
			}
			return index;
		}

		private  int CalcNullIndex (XmlNode value) {
			int index = 0;
			XmlNode parentNode = value.ParentNode;
			foreach(XmlNode node in parentNode.ChildNodes) { 
				if(node == value)
					return index;
				if(ShouldWriteNullCheckCode(node))
					index++;
			}
			return index;
		}

		private  bool HasFieldOperator (XmlNode value) {
			return HasConstantAttribute(value) ||
			HasCopyValueAttribute(value) ||
			HasDefaultValueAttribute(value) ||
			HasIncrementValueAttribute(value);
		}

		private  bool ShouldWriteNullCheckCode (XmlNode value) {
			if(value.NodeType == XmlNodeType.Comment)
				return false;
			if(HasOptionalPresence(value) && !HasFieldOperator(value))
				return true;
			if(HasDefaultValueAttribute(value) || HasCopyValueAttribute(value) || HasIncrementValueAttribute(value)) {
				if(HasOptionalPresence(value))
					return true;
			}
			return false;
		}

		private  bool ShouldWriteCheckPresenceMapCode (XmlNode value) {
			if(value.NodeType == XmlNodeType.Comment)
				return false;
			string[] forbidden = new string[] { "MsgSeqNum", "MessageEncoding" };
			for(int i = 0; i < forbidden.Length; i++) {
				if(forbidden[i] == Name(value))
					return false;
			}

			if(HasMandatoryPresence(value) && HasConstantAttribute(value))
				return false; // it seems that there is an error with mandatory presence true; // WAS false - PLEASE CHECK
			if(HasOptionalPresence(value) && HasConstantAttribute(value))
				return true;
			if(HasMandatoryPresence(value) &&
			   !HasCopyValueAttribute(value) &&
			   !HasDefaultValueAttribute(value) &&
			   !HasIncrementValueAttribute(value))
				return false;
			if(HasOptionalPresence(value) && !HasFieldOperator(value)) {
				return false;
			}
			if(HasMandatoryPresence(value)) {
				if(HasCopyValueAttribute(value) || HasDefaultValueAttribute(value) || HasIncrementValueAttribute(value))
					return true;
			}
			if(HasOptionalPresence(value)) {
				if(HasCopyValueAttribute(value) || HasDefaultValueAttribute(value) || HasIncrementValueAttribute(value))
					return true;
			}
			return false;
		}

		private  string GetDefaultValue (XmlNode value) {
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "default")
					return node.Attributes["value"].Value;
			}
			return string.Empty;
		}

		private  void WriteConstantValueCheckingCode (XmlNode value, string structName, string parentName, string tabString) {
			if(!WriteConstantCheckingCode)
				return;
			//WriteLine("#ifdef FAST_CHECK_CONSTANT_VALUES");
			if(IsString(value))
				WriteStringConstantValueCheckngCode(value, structName, parentName, tabString);
			else
				WriteNumericValueConstantCheckingCode(value, structName, parentName, tabString);
			//WriteLine("#endif");
		}

		private  void WriteNumericValueConstantCheckingCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "if(" + structName + "->" + Name(value) + " != " + GetFieldConstantValue(value) + ") this->LogError(\"" + structName + "::" + Name(value) + " != " + GetFieldConstantValue(value) + "\");");
		}

		private  void WriteStringConstantValueCheckngCode (XmlNode value, string structName, string parentName, string tabString) {
			WriteLine(tabString + "if(!this->FastCompareString("
			+ structName + "->" + Name(value) + ", " + structName + "->" + Name(value) + "Length, " +
			"\"" + GetFieldConstantValue(value) + "\"" + ", " + GetFieldConstantValue(value).Count() + ""
			+ ")) this->LogError(\"" + parentName + "Info::" + Name(value) + " != " + GetFieldConstantValue(value) + "\");");
		}
		bool ShouldSkipField(XmlNode node) {
			return node.Attributes["skip"] != null && node.Attributes["skip"].Value.ToLower() == "true";
		}
		string Name (XmlNode node) {
			if(node == null)
				throw new ArgumentException("node == null");
			if (node.Attributes == null) {
				throw new ArgumentException ("node.Attributes == null for " + node.Name.ToString () + "  " + node.InnerText);
			}
			return node.Attributes["name"] != null ? node.Attributes["name"].Value : "";
		}
		string ItemName(XmlNode node) {
			return Name(node) == "GroupMDEntries" ? "" : Name(node);
		}
		string PresenceIndexName(XmlNode node) {
			return Name(node) + "PresenceIndex";
		}
		string NullFlagName(XmlNode node) {
			return "IsNull" + Name(node);
		}

		int LevelCount = 1;

		string GetIemInfoPrefix (XmlNode value) {
			string prefix = Name(value);
			StringBuilder builder = new StringBuilder();
			foreach(char c in prefix)
				if(Char.IsUpper(c))
					builder.Append(c);
			return builder.ToString().ToLower();
		}

		string AttributeValue(XmlNode node, string attr) {
			return node.Attributes [attr].Value;
		}

		private  void ParseSequence (StructureInfo str, XmlNode value, string objectValueName, string parentClassCoreName, string tabString) {
			bool process_empty_pmap = HasAttribute (value, "process_empty_pmap", "true");

			StructureInfo info = GetOriginalStruct(value);
			if(info == null)
				info = GetStruct(value);
			if(info == null) {
				Console.WriteLine("Error: no struct found for " + value.ParentNode.Attributes["name"].Value);
			}
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine("");
			string methodName = HasOptionalPresence(value)? "ReadUInt32_Optional_Predict12": "ReadUInt32_Mandatory_Predict12";
			if(UseBmi)
				methodName += "_BMI";
			else 
				methodName += "_Simple";
			string count = objectValueName + "->" + Name (value) + "Count";
			if (ShouldWriteNullCheckCode (value)) {
				WriteLine (tabString + "if(!" + methodName + "((UINT32*)&(" + objectValueName + "->" + Name (value) + "Count))) {");
				WriteLine (tabString + "\t" + objectValueName + "->" + Name (value) + "Count = 0;");
				WriteLine (tabString + "\tnmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex (value) + ";");
				WriteLine (tabString + "}");
			} else {
				WriteLine (tabString + objectValueName + "->" + Name (value) + "Count = " + methodName + "();");
			}
			WriteLine(tabString + info.Name + "* " + itemInfo + " = NULL;");
			WriteLine("");

			string i = itemInfo + "Index";
			WriteLine (tabString + "for(int " + i + " = 0; " + i + " < " + count + "; " + i + "++) {");
			WriteLine (tabString + "\t" + itemInfo + " = " + info.GetFreeMethodName + "();");
			WriteLine (tabString + "\tfor(int i = 0; i < sizeof(" + info.Name + "); i += 64)");
			WriteLine (tabString + "\t\t__builtin_prefetch(((char*)" + itemInfo + ") + i, 0, _MM_HINT_T0);");
			WriteLine (tabString + "\t" + objectValueName + "->" + Name(value) + "[" + i + "] = " + itemInfo + ";");
			WriteLine (tabString + "}");

			WriteLine (tabString + "for(int " + i + " = 0; " + i + " < " + count + "; " + i + "++) {");
			WriteLine(tabString + "\t" + itemInfo + " = " + objectValueName + "->" + Name(value) + "[" + i + "];");
			LevelCount++;
			if(GetMaxPresenceBitCount(value) > 0) {
				WriteLine("");
				WriteParsePresenceMap(value, itemInfo, tabString + "\t");
			}
			WriteLine(tabString + "\tUINT64 nmap" + LevelCount + " = 0;");
			WriteLine("");

			string pmap = "pmap" + LevelCount;
			string nmap = "nmap" + LevelCount;
			if (process_empty_pmap) {
				WriteLine(tabString + "\tif(" + pmap + " != 0) {");
				tabString += "\t";
			}
			if (HasAttribute (value, "pmap1")) {
				WriteLine (tabString + "\tif(" + pmap + " == " + AttributeValue(value, "pmap1") + ") {");
				foreach(XmlNode node in value.ChildNodes)
					ParseValue(info, node, itemInfo, parentClassCoreName + Name(value), tabString + "\t\t", false, true, Convert.ToUInt64(AttributeValue(value, "pmap1")));
				if (GetMaxPresenceBitCount (value) > 0)
					WriteLine (tabString + "\t\t" + itemInfo + "->PresenceMap = " + pmap + ";");
				WriteLine (tabString + "\t\t" + itemInfo + "->NullMap = " + nmap + ";");
				WriteLine (tabString + "\t\tthis->" + info.PrevValueName + " = " + itemInfo + ";");
				WriteLine (tabString + "\t\tcontinue;");
				WriteLine (tabString + "\t}");
			}
			if (HasAttribute (value, "pmap2")) {
				WriteLine (tabString + "\tif(" + pmap + " == " + AttributeValue(value, "pmap2") + ") {");
				foreach(XmlNode node in value.ChildNodes)
					ParseValue(info, node, itemInfo, parentClassCoreName + Name(value), tabString + "\t\t", false, true, Convert.ToUInt64(AttributeValue(value, "pmap2")));
				if (GetMaxPresenceBitCount (value) > 0)
					WriteLine (tabString + "\t\t" + itemInfo + "->PresenceMap = " + pmap + ";");
				WriteLine (tabString + "\t\t" + itemInfo + "->NullMap = " + nmap + ";");
				WriteLine (tabString + "\t\tthis->" + info.PrevValueName + " = " + itemInfo + ";");
				WriteLine (tabString + "\t\tcontinue;");
				WriteLine (tabString + "\t}");
			}
			foreach(XmlNode node in value.ChildNodes)
				ParseValue(info, node, itemInfo, parentClassCoreName + Name(value), tabString + "\t", false, false, 0);
			if (GetMaxPresenceBitCount (value) > 0)
				WriteLine (tabString + "\t" + itemInfo + "->PresenceMap = pmap" + LevelCount + ";");
			WriteLine (tabString + "\t" + itemInfo + "->NullMap = nmap" + LevelCount + ";");

			if (process_empty_pmap) {
				WriteLine (tabString + "}");
				tabString = tabString.Substring (1);
				WriteLine (tabString + "\telse {");
				tabString += "\t";

				WriteLine(tabString + "\t" + itemInfo + "->Assign(this->" + info.PrevValueName + ");");
				foreach(XmlNode node in value.ChildNodes)
					ParseValue(info, node, itemInfo, parentClassCoreName + Name(value), tabString + "\t", true, false, 0);

				if (GetMaxPresenceBitCount (value) > 0) {
					WriteLine (tabString + "\t" + itemInfo + "->PresenceMap = pmap" + LevelCount + ";");
				}
				WriteLine (tabString + "\t" + itemInfo + "->NullMap = this->" + info.PrevValueName + "->NullMap;");

				WriteLine (tabString + "}");
				tabString = tabString.Substring (1);
			}
			WriteLine(tabString + "\tthis->" + info.PrevValueName + " = " + itemInfo + ";");
			LevelCount--;
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  bool ExtendedDecimal (XmlNode value) {
			foreach(XmlNode node in value.ChildNodes)
				if(node.Name == "exponent" || node.Name == "mantissa")
					return true;
			return false;
		}

		public bool UseBmi { get; set; }
		private string GetMethodName(XmlNode field, string method) {
			string finalName = string.Empty;
			if(HasAttribute(field, "fixed_size"))
				finalName = method + "_Fixed" + field.Attributes ["fixed_size"].Value.ToString();
			else if(HasAttribute(field, "predict"))
				finalName = method + "_Predict" + field.Attributes ["predict"].Value.ToString();
			else 
				finalName = method;
			
			if (field.Name == "int32" || field.Name == "uInt32" || field.Name == "int64" || field.Name == "uInt64" || field.Name == "decimal") {
				finalName += UseBmi? "_BMI": "_Simple";
			}
			return finalName;
		}

		private  void ParseByteVectorValue (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullByteVector())");
				WriteLine(tabString + "\tnmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "{");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Length");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Data");
				WriteLine(tabString + "}");
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + "ReadByteVector_Optional(" + info + "->" + Name(value) + ", &(" + info + "->" + Name(value) + "Length)" + ", " + GetMaxByteVectorSize(value) + ");");
				else
					WriteLine(tabString + "ReadByteVector_Mandatory(" + info + "->" + Name(value) + ", &(" + info + "->" + Name(value) + "Length)" + ", " + GetMaxByteVectorSize(value) + ");");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteByteVectorValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseDecimalValue (StructureInfo str, XmlNode value, string info, string tabString) {
			string methodName = HasOptionalPresence(value)? "ReadDecimal_Optional" : "ReadDecimal_Mandatory";
			methodName = GetMethodName (value, methodName);
			if(ShouldWriteNullCheckCode(value)) {
				string fullMethodName = methodName +"(&(" + info + "->" + Name(value) + "))";
				int ni = CalcNullIndex (value);
				WriteLine(tabString + "nmap" + LevelCount + " |= NULL_MAP_INDEX" + ni + " & (" + fullMethodName + " - 1);");
				return;
			}
			if(ExtendedDecimal(value))
				throw new Exception("Extended deciamal detected in template!");
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "{");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Mantissa");
				WriteLine(tabString + "\tSkipToNextField(); // " + Name(value) + " Exponent");
				WriteLine(tabString + "}");
			} else {
				WriteLine(tabString + methodName + "(&(" + info + "->" + Name(value) + "));");
			}
		}

		private  void ParseInt64Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullInt64())");
				WriteLine(tabString + "\tnmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + info + "->" + Name(value) + " = " + GetMethodName(value, "ReadInt64_Optional") + "();");
				else
					WriteLine(tabString + info + "->" + Name(value) + " = " + GetMethodName(value, "ReadInt64_Mandatory") + "();");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
				/*
				if(HasOperators(value)) {
					WriteLine(tabString + "else {");
					tabString += "\t";
					WriteInt64ValueOperatorsCode(str, value, info, tabString);
					tabString = tabString.Substring(1);
					WriteLine(tabString + "}");
				}*/
			}
		}

		private  void ParseUint64Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if(ShouldWriteNullCheckCode(value)) {
				WriteLine(tabString + "if(CheckProcessNullUInt64())");
				WriteLine(tabString + "\tnmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex(value) + ";");
				WriteLine(tabString + "else");
				tabString += "\t";
			}
			if(ShouldSkipField(value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
			} else {
				if(HasOptionalPresence(value))
					WriteLine(tabString + info + "->" + Name(value) + " = " + GetMethodName(value, "ReadUInt64_Optional") + "();");
				else
					WriteLine(tabString + info + "->" + Name(value) + " = " + GetMethodName(value, "ReadUInt64_Mandatory") + "();");
			}
			if(ShouldWriteNullCheckCode(value)) {
				tabString = tabString.Substring(1);
			}
		}

		private  void ParseInt32Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if (ShouldSkipField (value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
				return;
			}
			if(ShouldWriteNullCheckCode(value)) {
				string nullIndex = "NULL_MAP_INDEX" + CalcNullIndex (value);
				string fullMethodName = GetMethodName (value, "ReadInt32_Optional") + "(&(" + info + "->" + Name (value) + "))";
				WriteLine (tabString + "nmap" + LevelCount + " |= " + nullIndex + " & (" + fullMethodName + " - 1);");
				//WriteLine (tabString + "if(!" + GetMethodName(value, "ReadInt32_Optional") + "(&(" + info + "->" + Name(value) + ")))");
				//WriteLine(tabString + "\tnmap" + LevelCount + " |= " + nullIndex + ";");
				return;
			}
			if (HasOptionalPresence (value))
				WriteLine (tabString + info + "->" + Name (value) + " = " + GetMethodName(value, "ReadInt32_Optional") + "();");
			else
				WriteLine (tabString + info + "->" + Name (value) + " = " + GetMethodName(value, "ReadInt32_Mandatory") + "();");
		}

		private  void ParseUint32Value (StructureInfo str, XmlNode value, string info, string tabString) {
			if (ShouldSkipField (value)) {
				WriteLine(tabString + "SkipToNextField(); // " + Name(value));
				return;
			}
			if(ShouldWriteNullCheckCode(value)) {
				string nullIndex = "NULL_MAP_INDEX" + CalcNullIndex (value);
				string fullMethodName = GetMethodName (value, "ReadUInt32_Optional") + "(&(" + info + "->" + Name (value) + "))";
				WriteLine (tabString + "nmap" + LevelCount + " |= " + nullIndex + " & (" + fullMethodName + " - 1);");
				//WriteLine (tabString + "if(!" + GetMethodName(value, "ReadUInt32_Optional") + "(&(" + info + "->" + Name(value) + ")))");
				//WriteLine(tabString + "\tnmap" + LevelCount + " |= " + nullIndex + ";");
				return;
			}
			if (HasOptionalPresence (value))
				WriteLine (tabString + info + "->" + Name (value) + " = " + GetMethodName(value, "ReadUInt32_Optional") + "();");
			else
				WriteLine (tabString + info + "->" + Name (value) + " = " + GetMethodName(value, "ReadUInt32_Mandatory") + "();");
		}

		private  void ParseStringValue (StructureInfo str, XmlNode value, string info, string tabString) {
			string methodName = HasOptionalPresence (value) ? GetMethodName (value, "ReadString_Optional") : GetMethodName (value, "ReadString_Mandatory");
			bool hasFixedSize = HasAttribute (value, "fixed_size");
			if (hasFixedSize) {
				if (ShouldWriteNullCheckCode (value)) {
					string fullMethodName = methodName + "(" + info + "->" + Name (value) + ")";
					WriteLine (tabString + "nmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex (value) + " & (" + fullMethodName + " - 1);");
					//WriteLine (tabString + "if(!" + methodName + "(" + info + "->" + Name (value) + "))");
					//WriteLine (tabString + "\tnmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex (value) + ";");
					return;
				}
				WriteLine (tabString + methodName + "(" + info + "->" + Name (value) + ");");
			} else {
				if (ShouldWriteNullCheckCode (value)) {
					string fullMethodName = methodName + "(" + info + "->" + Name (value) + ", &(" + info + "->" + Name (value) + "Length)" + ")";
					WriteLine (tabString + "nmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex (value) + " & (" + fullMethodName + " - 1);");
					//WriteLine (tabString + "if(!" + methodName + "(" + info + "->" + Name (value) + ", &(" + info + "->" + Name (value) + "Length)" + "))");
					//WriteLine (tabString + "\tnmap" + LevelCount + " |= NULL_MAP_INDEX" + CalcNullIndex (value) + ";");
					return;
				}
				WriteLine (tabString + methodName + "(" + info + "->" + Name (value) + ", &(" + info + "->" + Name (value) + "Length)" + ");");
			}
		}

		private  void WriteDecimalValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteInt64ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteUint64ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteInt32ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteUint32ValueDefault (XmlNode value, string structName, string tabString) {
			WriteLine(tabString + structName + "->" + Name(value) + " = " + GetDefaultValue(value) + ";");
		}

		private  void WriteStringValueDefault (XmlNode value, string structName, string tabString) {
			ConstantStringInfo info = ConstantStrings.FirstOrDefault((i) => i.Node == value);
			WriteLine(tabString + structName + "->" + Name(value) + " = this->" + info.FieldName + ";");
			WriteLine(tabString + structName + "->" + Name(value) + "Length = " + GetDefaultValue(value).Length + ";");
		}

		private  void WriteUint32ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteUint32ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteInt32ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteInt32ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private void WriteSetCopyFlagCode(StructureInfo str, XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + " = this->" + str.PrevValueName + "->" + Name(value) + ";");
			//WriteLine(tabString + info + "->CopyCount++;");
		}

		private  void WriteDecimalValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteDecimalValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value))
				throw new Exception("TODO Increment decimal");
		}

		private  void WriteDecimalCopyOperatorCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "*((UNT64*)&(" + info + "->" + Name(value) + ")) = *((UINT64*)&(" + info + "->Prev" + Name(value) + "));");
		}

		private  void WriteByteVectorValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasCopyValueAttribute(value)) {
				WriteStringCopyValueCode(str, value, info, tabString);
			}
		}

		private  void WriteInt64ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteInt64ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteUint64ValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) {
				WriteUint64ValueDefault(value, info, tabString);
			}
			if(HasCopyValueAttribute(value)) {
				WriteSetCopyFlagCode(str, value, info, tabString);
			}
			if(HasIncrementValueAttribute(value)) {
				WriteSimpleIncrementValueCode(value, info, tabString);
			}
		}

		private  void WriteSimpleIncrementValueCode (XmlNode value, string info, string tabString) {
			WriteLine(tabString + info + "->" + Name(value) + "++;");
		}

		private  void WriteStringValueOperatorsCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if(HasDefaultValueAttribute(value)) { 
				WriteStringValueDefault(value, info, tabString);
			} else if(HasCopyValueAttribute(value)) {
				WriteStringCopyValueCode(str, value, info, tabString);
			}
		}

		private  void WriteStringCopyValueCode (StructureInfo str, XmlNode value, string info, string tabString) {
			if (HasAttribute (value, "union")) {
				WriteLine(tabString + info + "->" + Name(value) + GetTypeSuffix(value) + " = this->" + str.PrevValueName + "->" + Name(value) + GetTypeSuffix(value) + ";");
			}
			else {
				string method = "CopyString";
				method = GetMethodName (value, "CopyString"); 

				bool isFixedSize = HasAttribute (value, "fixed_size");
				if (isFixedSize) {
					WriteLine (tabString + "this->" + method + "(" + info + "->" + Name (value) + ", " + str.PrevValueName + "->" + Name (value) + ");");				
				} else {
					if(HasAttribute(value, "predict"))
						WriteLine (tabString + "this->" + method + "(" + info + "->" + Name (value) + ", " + str.PrevValueName + "->" + Name (value) + ");");
					else 
						WriteLine (tabString + "this->" + method + "(" + info + "->" + Name (value) + ", " + str.PrevValueName + "->" + Name (value) + ", " + str.PrevValueName + "->" + Name (value) + "Length" + ");");
					WriteLine (tabString + info + "->" + Name (value) + "Length = this->" + str.PrevValueName + "->" + Name (value) + "Length;");
				}
			}
		}

		private bool CanParseValue(XmlNode value) {
			if(HasConstantAttribute(value))
				return false;
			if(value.NodeType == XmlNodeType.Comment)
				return false;
			string[] forbidden = { "MessageType", "ApplVerID", "BeginString", "SenderCompID", "MessageEncoding" };
			string name = Name(value);
			for(int i = 0; i < forbidden.Length; i++)
				if(forbidden[i] == name)
					return false;
			return true;
		}

		private  void ParseValue (StructureInfo str, XmlNode value, string objectValueName, string classCoreName, string tabString, bool skipOptionalPresence, bool useSpecialPresenceMap, ulong presenceMap) {
			ParseValue(str, value, objectValueName, classCoreName, tabString, false, null, null, skipOptionalPresence, useSpecialPresenceMap, presenceMap);
		}

		private void WriteSkipCode(string tabStrings, string fieldName) {
			WriteLine(tabStrings + "SkipToNextField(); // " + fieldName);
		}
		bool Contains(List<SnapshotFieldInfo> fields, XmlNode node) {
			foreach(SnapshotFieldInfo info in fields) {
				if(info.FieldName == Name(node))
					return true;
			}
			return false;
		}
		bool IsPresenceAllowed(XmlNode value, ulong pmap) {
			if (!ShouldWriteCheckPresenceMapCode (value))
				return true;
			int index = CalcFieldPresenceIndex (value);
			ulong[] pmapBit = new ulong[] {
				0x0000000000000040L,
				0x0000000000000020L,
				0x0000000000000010L,
				0x0000000000000008L,
				0x0000000000000004L,
				0x0000000000000002L,
				0x0000000000000001L,
				0x0000000000004000L,
				0x0000000000002000L,
				0x0000000000001000L,
				0x0000000000000800L,
				0x0000000000000400L,
				0x0000000000000200L,
				0x0000000000000100L,
				0x0000000000400000L,
				0x0000000000200000L,
				0x0000000000100000L,
				0x0000000000080000L,
				0x0000000000040000L,
				0x0000000000020000L,
				0x0000000000010000L,
				0x0000000040000000L,
				0x0000000020000000L,
				0x0000000010000000L,
				0x0000000008000000L,
				0x0000000004000000L,
				0x0000000002000000L,
				0x0000000001000000L,
				0x0000004000000000L,
				0x0000002000000000L,
				0x0000001000000000L,
				0x0000000800000000L,
				0x0000000400000000L,
				0x0000000200000000L,
				0x0000000100000000L,
				0x0000400000000000L,
				0x0000200000000000L,
				0x0000100000000000L,
				0x0000080000000000L,
				0x0000040000000000L,
				0x0000020000000000L,
				0x0000010000000000L,
				0x0040000000000000L,
				0x0020000000000000L,
				0x0010000000000000L,
				0x0008000000000000L,
				0x0004000000000000L,
				0x0002000000000000L,
				0x0001000000000000L,
				0x4000000000000000L,
				0x2000000000000000L,
				0x1000000000000000L,
				0x0800000000000000L,
				0x0400000000000000L,
				0x0200000000000000L,
				0x0100000000000000L
			};
			return (pmapBit [index] & pmap) != 0;
		}
		private  void ParseValue (StructureInfo str, 
			XmlNode value, 
			string objectValueName, 
			string classCoreName, 
			string tabString, 
			bool skipNonAllowed, 
			List<SnapshotFieldInfo> allowedFields, 
			List<string> parsed, 
			bool skipOptionalPresence,
			bool useSepcialPresenceMap,
			ulong specialPresenceMap) {

			if(value.Name == "length")
				return;

			// skip constant value WHY??????!!!!!
			if(!CanParseValue(value))
				return;
						
			if(skipNonAllowed) { 
				if(!Contains(allowedFields, value)) {
					WriteSkipCode(tabString, Name(value));
					return;
				}
				parsed.Add(Name(value));
			}

			bool isPresenceAllowed = IsPresenceAllowed (value, specialPresenceMap);
			bool isOptionalPresence = ShouldWriteCheckPresenceMapCode (value);

			bool writeParseCode = true;
			if (isOptionalPresence) {
				if (skipOptionalPresence)
					writeParseCode = false;
				else if (useSepcialPresenceMap && !isPresenceAllowed)
					writeParseCode = false;
			}
			bool writePresenceCheck = isOptionalPresence && !skipOptionalPresence && !useSepcialPresenceMap;

			if(writePresenceCheck) {
				string name = HasOptionalPresence(value)? "CheckOptionalFieldPresence": "CheckMandatoryFieldPresence";
				WriteLine(tabString + "if(" + name + "(pmap" + LevelCount + ", PRESENCE_MAP_INDEX" + CalcFieldPresenceIndex(value) + ")) {");
				tabString += "\t";
			}

			if (writeParseCode) {
				if (IsString (value))
					ParseStringValue (str, value, objectValueName, tabString);
				else if (value.Name == "uInt32")
					ParseUint32Value (str, value, objectValueName, tabString);
				else if (value.Name == "int32")
					ParseInt32Value (str, value, objectValueName, tabString);
				else if (value.Name == "uInt64")
					ParseUint64Value (str, value, objectValueName, tabString);
				else if (value.Name == "int64")
					ParseInt64Value (str, value, objectValueName, tabString);
				else if (value.Name == "decimal")
					ParseDecimalValue (str, value, objectValueName, tabString);
				else if (IsByteVector (value))
					ParseByteVectorValue (str, value, objectValueName, tabString);
				else if (value.Name == "sequence")
					ParseSequence (str, value, objectValueName, classCoreName, tabString);
				else {
					WriteLine (tabString + "TODO!!!!!!!!");
					Console.WriteLine ("ERROR: found undefined field " + value.Name);
					throw new NotImplementedException ("ERROR: found undefined field " + value.Name);
				}
				if (HasConstantAttribute (value))
					WriteConstantValueCheckingCode (value, objectValueName, classCoreName, tabString);
			}

			if (useSepcialPresenceMap && !writeParseCode) {
				WriteApplyOperatorsCode(str, value, objectValueName, tabString);
			}
			else if(writePresenceCheck) {
				tabString = tabString.Substring (1);
				WriteLine (tabString + "}");
				WriteLine (tabString + "else {");
				WriteApplyOperatorsCode(str, value, objectValueName, tabString + "\t");
				WriteLine(tabString + "}");
			}
		}

		private void WriteApplyOperatorsCode(StructureInfo str, XmlNode value, string info, string tabString) {
			if(IsString(value))
				WriteStringValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "uInt32")
				WriteUint32ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "int32")
				WriteInt32ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "uInt64")
				WriteUint64ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "int64")
				WriteInt64ValueOperatorsCode(str, value, info, tabString);
			else if(value.Name == "decimal")
				WriteDecimalValueOperatorsCode(str, value, info, tabString);
			else if(IsByteVector(value))
				WriteByteVectorValueOperatorsCode(str, value, info, tabString);
		}

		private  void PrintStringValue (XmlNode value, string info, string tabString, int tabsCount) {
			if (HasAttribute (value, "fixed_size")) {
				WriteLine(tabString + "PrintString(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + value.Attributes["fixed_size"].Value + ", " + tabsCount + ");");
			}
			else 
				WriteLine(tabString + "PrintString(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ", " + tabsCount + ");");
		}

		private  void PrintUInt32Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintUInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintInt32Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintUInt64Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintUInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintInt64Value (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + tabsCount + ");");
		}

		private  void PrintDecimalValue (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintDecimal(\"" + Name(value) + "\", &(" + info + "->" + Name(value) + "), " + tabsCount + ");");
		}

		private  void PrintByteVectorValue (XmlNode value, string info, string tabString, int tabsCount) {
			WriteLine(tabString + "PrintByteVector(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length, " + tabsCount + ");");
		}

		private  void PrintXmlStringValue (XmlNode value, string info, string tabString) {
			if (HasAttribute (value, "fixed_size")) {
				WriteLine(tabString + "PrintXmlString(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + value.Attributes["fixed_size"].Value + ");");
			}
			else 
				WriteLine(tabString + "PrintXmlString(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ");");
		}

		private  void PrintXmlUInt32Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlUInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlInt32Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlInt32(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlUInt64Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlUInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlInt64Value (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlInt64(\"" + Name(value) + "\", " + info + "->" + Name(value) + ");");
		}

		private  void PrintXmlDecimalValue (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlDecimal(\"" + Name(value) + "\", &(" + info + "->" + Name(value) + "));");
		}

		private  void PrintXmlByteVectorValue (XmlNode value, string info, string tabString) {
			WriteLine(tabString + "PrintXmlByteVector(\"" + Name(value) + "\", " + info + "->" + Name(value) + ", " + info + "->" + Name(value) + "Length" + ");");
		}

		private  void PrintXmlSequence (XmlNode value, string objectValueName, string parentClassCoreName, string tabString) {
			StructureInfo info = GetOriginalStruct(value);
			if(info == null)
				info = GetStruct(value);
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine(tabString + "PrintXmlInt32(\"" + Name(value) + "Count\", " + objectValueName + "->" + Name(value) + "Count);");
			WriteLine("");
			string countField = objectValueName + "->" + Name(value) + "Count";

			WriteLine(tabString + info.Name + "* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + countField + "; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = " + objectValueName + "->" + Name(value) + "[i];");
			WriteLine(tabString + "\tPrintXmlItemBegin(\"item\", i);");
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "length")
					continue;
				LevelCount++;
				PrintXmlValue(node, itemInfo, parentClassCoreName + Name(value), tabString + "\t");
				LevelCount--;
			}
			WriteLine(tabString + "\tPrintXmlItemEnd(\"item\", i);");
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  void PrintSequence (XmlNode value, string objectValueName, string parentClassCoreName, string tabString, int tabsCount) {
			StructureInfo info = GetOriginalStruct(value);
			if(info == null)
				info = GetStruct(value);
			string itemInfo = GetIemInfoPrefix(value) + "ItemInfo";
			WriteLine(tabString + "PrintInt32(\"" + Name(value) + "Count\", " + objectValueName + "->" + Name(value) + "Count, " + tabsCount + ");");
			WriteLine("");
			string countField = objectValueName + "->" + Name(value) + "Count";

			WriteLine(tabString + info.Name + "* " + itemInfo + " = NULL;");
			WriteLine("");
			WriteLine(tabString + "for(int i = 0; i < " + countField + "; i++) {");
			WriteLine(tabString + "\t" + itemInfo + " = " + objectValueName + "->" + Name(value) + "[i];");
			WriteLine(tabString + "\tPrintItemBegin(\"item\", i, " + tabsCount + ");");
			foreach(XmlNode node in value.ChildNodes) {
				if(node.Name == "length")
					continue;
				LevelCount++;
				tabsCount++;
				PrintValue(node, itemInfo, parentClassCoreName + Name(value), tabString + "\t", tabsCount);
				tabsCount--;
				LevelCount--;
			}
			WriteLine(tabString + "\tPrintItemEnd(" + tabsCount + ");");
			WriteLine(tabString + "}");
			WriteLine("");
		}

		private  void PrintValue (XmlNode value, string objectValueName, string classCoreName, string tabString, int tabsCount) {
			if(value.Name == "length")
				return;
			
			// skip constant value WHY??????!!!!!
			if(HasConstantAttribute(value))
				return;
			if(ShouldWriteNullCheckCode(value)) { 
				int nullIndex = CalcNullIndex(value);
				WriteLine(tabString + "if((" + objectValueName + "->NullMap & NULL_MAP_INDEX" + nullIndex + ") == 0)");
				tabString += "\t";
			}

			if(IsString(value))
				PrintStringValue(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "uInt32")
				PrintUInt32Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "int32")
				PrintInt32Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "uInt64")
				PrintUInt64Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "int64")
				PrintInt64Value(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "decimal")
				PrintDecimalValue(value, objectValueName, tabString, tabsCount);
			else if(IsByteVector(value))
				PrintByteVectorValue(value, objectValueName, tabString, tabsCount);
			else if(value.Name == "sequence")
				PrintSequence(value, objectValueName, classCoreName, tabString, tabsCount);
			else {
				WriteLine(tabString + "TODO!!!!!!!!");
				Console.WriteLine("ERROR: found undefined field " + value.Name);
				throw new NotImplementedException("ERROR: found undefined field " + value.Name);
			}
			if(ShouldWriteNullCheckCode(value))
				tabString = tabString.Substring(1);
		}

		private  void PrintXmlValue (XmlNode value, string objectValueName, string classCoreName, string tabString) {
			if(value.Name == "length")
				return;

			// skip constant value WHY??????!!!!!
			if(HasConstantAttribute(value))
				return;

			if(ShouldWriteNullCheckCode(value)) {
				int nullIndex = CalcNullIndex(value);
				WriteLine(tabString + "if((" + objectValueName + "->NullMap & NULL_MAP_INDEX" + nullIndex + ") == 0)");
				tabString += "\t";
			}
			if(IsString(value))
				PrintXmlStringValue(value, objectValueName, tabString);
			else if(value.Name == "uInt32")
				PrintXmlUInt32Value(value, objectValueName, tabString);
			else if(value.Name == "int32")
				PrintXmlInt32Value(value, objectValueName, tabString);
			else if(value.Name == "uInt64")
				PrintXmlUInt64Value(value, objectValueName, tabString);
			else if(value.Name == "int64")
				PrintXmlInt64Value(value, objectValueName, tabString);
			else if(value.Name == "decimal")
				PrintXmlDecimalValue(value, objectValueName, tabString);
			else if(IsByteVector(value))
				PrintXmlByteVectorValue(value, objectValueName, tabString);
			else if(value.Name == "sequence")
				PrintXmlSequence(value, objectValueName, classCoreName, tabString);
			else {
				WriteLine(tabString + "TODO!!!!!!!!");
				Console.WriteLine("ERROR: found undefined field " + value.Name);
				throw new NotImplementedException("ERROR: found undefined field " + value.Name);
			}
			if(ShouldWriteNullCheckCode(value))
				tabString = tabString.Substring(1);
		}

		private  bool HasOperators (XmlNode value) {
			return HasCopyValueAttribute(value) || HasDefaultValueAttribute(value) || HasIncrementValueAttribute(value);
		}

		private  bool IsMandatoryField (XmlNode value) {
			return !HasAttribute(value, "presence") || value.Attributes["presence"].Value == "mandatory";
		}
	}

	public class EnumInfo {
		static string Prefix = "lmc";

		public int Value { get; set; }

		public string EnumName { 
			get;
			set;
		}

		public string EnumFullName { 
			get{ return "LogMessageCode::" + EnumName; }
		}

		public void ParseEnum (string line) {
			string[] tokens = line.Replace(" ", "").Split(new char[] { '=', ',' }, 2);
			if(tokens.Length != 2) {
				Console.WriteLine("error: invalid enum line!");
				throw new ArgumentException();
			}
			EnumName = tokens[0].Trim();
			if(tokens[1].EndsWith(","))
				tokens[1] = tokens[1].Substring(0, tokens[1].Length - 1);
			Value = int.Parse(tokens[1]);
		}

		string messageText;

		public string MessageText { 
			get { return messageText; }
			set {  
				if(MessageText == value)
					return;
				messageText = value;
				if(string.IsNullOrEmpty(EnumName))
					EnumName = GetEnumName();
			}
		}

		string GetEnumName () { 
			if(string.IsNullOrEmpty(MessageText))
				return string.Empty;
			string res = MessageText;

			while(true) {
				if(!char.IsLetterOrDigit(res[res.Length - 1]))
					res = res.Substring(0, res.Length - 1);
				else
					break;
			}

			bool end = false;
			while(!end) {
				end = true;
				foreach(char c in res) {
					if(!char.IsLetterOrDigit(c) && c != '_') {
						res = res.Replace(c, '_');
						end = false;
						break;
					}
				}
			}

			res = res.Replace("____", "_");
			res = res.Replace("___", "_");
			res = res.Replace("__", "_");
		
			res = Prefix + res;
			return res;
		}
	}

	public class TextFile {
		public TextFile () {
			Lines = new List<string>();
			OriginalLines = new List<string>();
		}

		public string FileName { get; set; }

		public bool Modified {
			get{ 
				if(OriginalLines.Count != Lines.Count)
					return true;

				for(int i = 0; i < OriginalLines.Count; i++) {
					if(!string.Equals(Lines[i], OriginalLines[i])) {
						return true;
					}
				}
				return false;
			}
		}
		public void NextLine() {
			Line++;
		}
		public int FindString (string searchString) {
			if(Line < 0 || Line > LineCount)
				Line = 0;
			for(int i = Line; i < LineCount; i++) {
				if(Lines[i].Contains(searchString)) {
					Line = i;
					return i;
				}
			}
			Line = -1;
			return -1;
		}

		public bool LoadFromFile (string fileName) {
			FileName = fileName;
			Lines.Clear();
			try {
				StreamReader reader = new StreamReader(fileName);
				string line = null;
				while((line = reader.ReadLine()) != null) {
					Lines.Add(line);
					OriginalLines.Add((string)line.Clone());
				}
				reader.Close();
			} catch(Exception) { 
				return false;
			}
			return true;
		}

		public bool Save () {
			return WriteToFile(FileName);
		}

		bool WriteToFile (string fileName) {
			if(!Modified) {
				//Console.WriteLine(FileName + " was not changed. skip update.");
				return true;
			}
			try {
				StreamWriter writer = new StreamWriter(fileName);
				foreach(string str in Lines)
					writer.WriteLine(str);
				writer.Flush();
				writer.Close();
			} catch(Exception) {
				return false;
			}
			//Modified = false;
			return true;
		}

		public List<string> Lines { get; set; }
		protected List<string> OriginalLines { get; set; }

		public int Line { get; set; }

		public string LineText { get { return Lines[Line]; } }

		public void GoTo (int line) {
			Line = Math.Min(line, Lines.Count - 1);
		}

		public void Replace (int index, string newLine) { 
			//Modified = true;
			Lines[index] = newLine;
		}

		public void Remove (int index) { 
			//Modified = true;
			Lines.RemoveAt(index);
		}

		public void Add (int index, string newLine) {
			//Modified = true;
			Lines.Insert(index, newLine);
		}

		public void Add (string newLine) {
			//Modified = true;
			Lines.Insert(Line, newLine);
			Line++;
		}

		public int LineCount { get { return Lines.Count; } }

		public void SetCurrentLine (string newText) {
			//Modified = true;
			Lines[Line] = newText;
		}

		public void ClearRegion (string regionName) {
			GoTo(0);
			if(FindString(regionName) == -1)
				throw new ArgumentException(regionName + " region not found");
			int startLine = Line + 1;
			int endLine = FindString("endregion");
			if(endLine == -1 || !LineText.Contains("pragma"))
				throw new ArgumentException("pragma region not found");
			for(int i = 0; i < endLine - startLine; i++)
				Lines.RemoveAt(startLine);
			//Console.WriteLine("cleared region '" + regionName + "' removed lines from " + startLine + " to " + endLine);
			Line = startLine;
		}
	}

	class MainClass {
		private static Dictionary<string, string> m_params = new Dictionary<string, string>();

		public static void Main (string[] args) {
			OptionSet p = new OptionSet() { {"x|xml=", "Full path to config XML",
					v => m_params.Add("x", v)
				}, {"d|data=", "Path to directory with data files",
					v => m_params.Add("d", v)
				}, {"o|out=", "Output directory",
					v => m_params.Add("o", v)
				}, {"s|src=", "C++ sources directory",
					v => m_params.Add("s", v)
				}, {"f|fast", "Generate Fast protocol code",
					v => m_params.Add("f", v)
				}, {"ax|asts_xml=", "Path to Asts templates file xml",
					v => m_params.Add("ax", v)
				}, {"sx|spectra_xml=", "Path to Spectra templates file xml",
					v => m_params.Add("sx", v)
				}, {"acfg|asts_cfg=", "Path to asts config file xml",
					v => m_params.Add("acfg", v)
				}, {"scfg|spectra_cfg=", "Path to spectra config file xml",
					v => m_params.Add("scfg", v)
				}, {"fh|fast__source_h=", "Path to FastProtocolManager.h file",
					v => m_params.Add("fh", v)
				}, {"fc|fast__source_cpp=", "Path to FastProtocolManager.cpp file",
					v => m_params.Add("fc", v)
				}, {"ft|fast_types=", "Path to FastTypes.h file",
					v => m_params.Add("ft", v)
				}, {"rb|robot_source_cpp=", "Path to Robot.cpp file",
					v => m_params.Add("rb", v)
				}, {"incCurr|fast_check_const", "Write constant checking code in fast protocol files",
					v => m_params.Add("incCurr", v)
				}
			};
			try {
				p.Parse(args);
			} catch(OptionException e) {
				Console.WriteLine(e.Message);
			}
			//if(!CopyFastServerConfigurationFile()) {
			//	Console.WriteLine("exit.");
			//	return;
			//}

			GenerateLogMessages();
			GenerateStatisticMessages();
			GenerateFast();
		}
		static void GenerateFast() {
			string value;
			Console.WriteLine("generate fast protocol...");
			if(!m_params.TryGetValue("f", out value)) {
				Console.WriteLine("skip.");
				return;
			}
			FastTemplatesCodeGenerator generator = new FastTemplatesCodeGenerator();
			generator.WriteConstantCheckingCode = m_params.TryGetValue("incCurr", out value);

			if(!m_params.TryGetValue("fc", out value)) {
				Console.WriteLine("FastProtocolManager.cpp file not specified. skip generation.");
				return;
			}
			generator.ManagerSourceFileCpp = value;
			if(!m_params.TryGetValue("fh", out value)) {
				Console.WriteLine("FastProtocolManager.h file not specified. skip generation.");
				return;
			}
			generator.ManagerSourceFileH = value;
			if(!m_params.TryGetValue("ft", out value)) {
				Console.WriteLine("FastTypes file not specified. skip generation.");
				return;
			}
			generator.SourceTypes = value;
			if(!m_params.TryGetValue("ax", out value)) {
				Console.WriteLine("Asts template file not specified. skip generation.");
				return;
			}
			generator.AstsTemplateFile = value;
			if(!m_params.TryGetValue("sx", out value)) {
				Console.WriteLine("Spectra template file not specified. skip generation.");
				return;
			}
			generator.SpectraTemplateFile = value;
			if(!m_params.TryGetValue("rb", out value)) {
				Console.WriteLine("Robot.cpp file not specified. skip generation.");
				return;
			}
			generator.RobotCpp = value;
			if(!m_params.TryGetValue("acfg", out value)) {
				Console.WriteLine("Asts config file not specified. skip generation.");
				return;
			}
			generator.AstsServerConfigFileName = value;
			if(!m_params.TryGetValue("scfg", out value)) {
				Console.WriteLine("Spectra config file not specified. skip generation.");
				return;
			}
			generator.FortsServerConfigFileName = value;

			if(!generator.Generate()) {
				Console.WriteLine("generate fast protocol - failed.");
				return;
			}
			Console.WriteLine("generate fast protocol - done.");
		}

		static string LogMessageCodes_GeneratedCode = "LogMessageCodes_GeneratedCode";
		static string LogMessagesProvider_InitializeLogMessageText_GeneratedCode = "LogMessagesProvider_InitializeLogMessageText_GeneratedCode";
		static string ProgramStatistics_GeneratedCode = "ProgramStatistics_GeneratedCode";
		static string ProgramStatistics_Enum = "ProgramStatistics_Enum";
		static string ProgramStatistics_GeneratedFields = "ProgramStatistics_GeneratedFields";
		static string ProgramStatistics_GeneratedMethods = "ProgramStatistics_GeneratedMethods";
		static string ProgramStatistics_GeneratedClearCode = "ProgramStatistics_GeneratedClearCode";

		public class EnumText { 
			public string Value { get; set; }
			public string Text { get; set; }
			public bool IsArray { get; set; }
			public int Size { get; set; }
		}

		public static void GenerateStatisticMessages() {
			Console.WriteLine("generate statistic messages...");
			List<TextFile> files = LoadSourceFiles();
			if(files == null)
				throw new Exception("can't load source files ");

			TextFile file = GetFileWithRegion(ProgramStatistics_GeneratedCode, files);
			if (file == null) {
				Console.WriteLine ("error: can't find file containing '" + ProgramStatistics_GeneratedCode + "' region");
				throw new Exception ("error: can't find file containing '" + ProgramStatistics_GeneratedCode + "' region");
			}
			file.Line = 0;
			int start = file.FindString (ProgramStatistics_Enum);
			if (start == -1) {
				Console.WriteLine ("error: can't find '" + ProgramStatistics_Enum + "' region");
				throw new Exception ("error: can't find '" + ProgramStatistics_Enum + "' region");
			}
			int end = file.FindString ("endregion");
			List<EnumText> values = new List<EnumText> ();

			for (int i = start + 1; i < end;) {
				file.Line = i;
				string enumString = file.LineText.Trim();
				EnumText et = new EnumText ();
				if (enumString.StartsWith ("//")) {
					et.Text = enumString.Substring (2).Trim();
					i++;
					file.Line = i;
				}
				enumString = file.LineText.Trim();
				if (string.IsNullOrEmpty (enumString)) {
					i++; continue;
				}
				string[] lines = enumString.Split (',');
				if (lines == null || lines.Length == 0) {
					i++;
					continue;
				}
				if (lines[0].Contains ('=')) {
					lines [0] = lines [0].Split ('=')[0].Trim ();
				}
				et.Value = lines [0];
				if (lines.Length > 0 && !string.IsNullOrEmpty (lines [1])) {
					et.Text = lines [1].Trim ().Substring (2).Trim();
				}
				if (string.IsNullOrEmpty (et.Text))
					et.Text = et.Value.Substring (1);
				if (et.Text.Contains ('[')) {
					int sizeStart = et.Text.IndexOf('[');
					int sizeEnd = et.Text.IndexOf(']');
					string length = et.Text.Substring(sizeStart + 1, sizeEnd - sizeStart - 1).Trim();
					et.Size = int.Parse(length);
					et.IsArray = true;
					et.Text = et.Text.Substring(0, sizeStart);
				}
				i++;
				values.Add (et);
			}
			file.Line = 0;
			file.ClearRegion (ProgramStatistics_Enum);
			for (int i = 0; i < values.Count; i++) {
				if(values[i].IsArray)
					file.Add ("\t" + values [i].Value + " = " + i + ", // " + values [i].Text + "[" + values[i].Size + "]");
				else 
					file.Add ("\t" + values [i].Value + " = " + i + ", // " + values [i].Text);
			}

			if (file.FindString (ProgramStatistics_GeneratedCode) == -1) {
				Console.WriteLine ("error: can't find '" + ProgramStatistics_GeneratedCode + "' region");
				throw new Exception ("error: can't find '" + ProgramStatistics_GeneratedCode + "' region");
			}

			file.Line = 0;
			file.ClearRegion (ProgramStatistics_GeneratedFields);
			for (int i = 0; i < values.Count; i++) {
				if (!values [i].IsArray)
					continue;
				file.Add ("\tint\t\t\tm_" + values [i].Value + "[" + values [i].Size + "];");
			}

			file.Line = 0;
			file.ClearRegion (ProgramStatistics_GeneratedCode);
			file.Add ("\t\tthis->m_itemsCount = " + values.Count + ";");
			file.Add ("\t\tthis->m_counts = new int[ this->m_itemsCount ];");
			file.Add ("\t\tthis->m_changed = new bool[ this->m_itemsCount ];");
			file.Add ("\t\tthis->m_names = new const char*[" + values.Count() +"];");
			for (int i = 0; i < values.Count; i++) {
				if (!values [i].IsArray)
					continue;
				file.Add ("\t\tmemset(this->m_" + values[i].Value + ", 0, sizeof(int) * " + values[i].Size + ");");
			}
			for (int i = 0; i < values.Count; i++) {
				file.Add ("\t\tthis->m_names[" + i + "] = \"" + values[i].Text + "\";");
			}

			file.Line = 0;
			file.ClearRegion (ProgramStatistics_GeneratedMethods);
			file.Add ("\tinline int* CounterIndex(Counters c) {");
			for (int i = 0; i < values.Count; i++) {
				if (!values [i].IsArray)
					continue;
				file.Add ("\t\tif(c == Counters::" + values[i].Value + ")");
				file.Add ("\t\t\treturn (int*)this->m_" + values [i].Value + ";");
			}
			file.Add ("\t\treturn 0;");
			file.Add ("\t}");

			file.Add ("\tinline int CounterSize(Counters c) {");
			for (int i = 0; i < values.Count; i++) {
				if (!values [i].IsArray)
					continue;
				file.Add ("\t\tif(c == Counters::" + values[i].Value + ")");
				file.Add ("\t\t\treturn " + values [i].Size + ";");
			}
			file.Add ("\t\treturn 0;");
			file.Add ("\t}");
			file.Line = 0;
			file.ClearRegion (ProgramStatistics_GeneratedClearCode);
			for (int i = 0; i < values.Count; i++) {
				if (!values [i].IsArray)
					continue;
				file.Add ("\t\tmemset(this->m_" + values[i].Value + ", 0, sizeof(int) * " + values[i].Size + ");");
			}

			if(file.Modified && !file.Save())
				throw new IOException("error: cannot update file " + file.FileName);
			
			Console.WriteLine("done.");
		}

		public static void GenerateLogMessages () { 
			Console.WriteLine("generate log messages...");
			List<TextFile> files = LoadSourceFiles();
			if(files == null)
				return;

			TextFile enumFile = GetFileWithRegion(LogMessageCodes_GeneratedCode, files);
			TextFile msgInitFile = GetFileWithRegion(LogMessagesProvider_InitializeLogMessageText_GeneratedCode, files);

			if(enumFile == null) {
				Console.WriteLine("error: can't find file containing 'LogMessageCodes_GeneratedCode' region");
				throw new Exception("can't find file containing 'LogMessageCodes_GeneratedCode' region");
			}
			if(msgInitFile == null) {
				Console.WriteLine("error: can't find file containing 'LogMessagesProvider_InitializeLogMessageText_GeneratedCode' region");
				throw new Exception("can't find file containing 'LogMessagesProvider_InitializeLogMessageText_GeneratedCode' region");
			}

			List<EnumInfo> availableEnums = GetAvailableEnums(enumFile, msgInitFile);
			//Console.WriteLine("found existing enums " + availableEnums.Count);
			//foreach(EnumInfo info in availableEnums) {
			//	Console.WriteLine("existing enum: " + info.EnumName + " = " + info.Value + " -> " + info.MessageText);
			//}
			int count = availableEnums.Count;
			FindInitializeStringConstants(files, availableEnums);
			if(availableEnums.Count != count) {
				WriteLogMessageCodeEnumDeclaration(enumFile, availableEnums);
				WriteLogMessageTextInitializationCode(msgInitFile, availableEnums);
			}

			foreach(TextFile file in files) {
				if(!file.Modified) {
					//Console.WriteLine(file.FileName + " was not modified. skip save");
					continue;
				}
				if(!file.Save())
					throw new IOException("error: cannot update file " + file.FileName);
			}

			Console.WriteLine("done.");
		}

		public static void WriteLogMessageTextInitializationCode (TextFile file, List<EnumInfo> enums) {
			file.ClearRegion(LogMessagesProvider_InitializeLogMessageText_GeneratedCode);
			foreach(EnumInfo info in enums) {
				string code = "\tthis->m_logMessageText[" + info.EnumFullName + "] = \"" + info.MessageText + "\";";
				file.Add(code);
				//Console.WriteLine(code);
			}
		}

		public static void WriteLogMessageCodeEnumDeclaration (TextFile file, List<EnumInfo> enums) {
			file.ClearRegion(LogMessageCodes_GeneratedCode);
			for(int i = 0; i < enums.Count; i++) {
				string code = "\t" + enums[i].EnumName + " = " + enums[i].Value;
				if(i < enums.Count - 1)
					code += ",";
				file.Add(code);
				//Console.WriteLine(code);
			}
		}

		public static void FindInitializeStringConstants (List<TextFile> files, List<EnumInfo> enums) {
			foreach(TextFile file in files) {
				FindInitializeStringConstants(file, enums);
			}
		}

		public static void FindInitializeStringConstants (TextFile file, List<EnumInfo> enums) {
			for(int i = 0; i < file.LineCount; i++) {
				file.GoTo(i);
				if(!file.LineText.Contains("DefaultLogManager"))
					continue;
				if(!file.LineText.Contains(';'))
					continue;
				if(!file.LineText.Contains("->"))
					continue;
				string[] tokens = file.LineText.Split(new string[] { "::", "->" }, StringSplitOptions.RemoveEmptyEntries);
				if(tokens[1] != "Default")
					continue;
				int index = 0;
				while(true) {
					index = file.LineText.IndexOf('"');
					int endIndex = file.LineText.IndexOf('"', index + 1);
					if(index == -1)
						break;
					if(endIndex == -1)
						break;
					string message = file.LineText.Substring(index, endIndex - index + 1);
					EnumInfo info = new EnumInfo();
					info.MessageText = message.Replace("\"", "");
					info.Value = GetMaxEnumValue(enums) + 1;
					enums.Add(info);
					file.SetCurrentLine(file.LineText.Replace(message, info.EnumFullName)); 
					//Console.WriteLine(file.FileName + ": replaced " + message + " with " + info.EnumFullName);
					index = endIndex + 1;
				}
			}
		}

		public static int GetMaxEnumValue (List<EnumInfo> enums) {
			if(enums.Count == 0)
				return 0;
			return enums.Max(i => i.Value);
		}

		public static List<EnumInfo> GetAvailableEnums (TextFile enumFile, TextFile msgInitFile) {
			List<EnumInfo> res = new List<EnumInfo>();

			enumFile.GoTo(0);
			int startPos = enumFile.FindString(LogMessageCodes_GeneratedCode);
			int endPos = enumFile.FindString("endregion");

			if(startPos == -1) {
				Console.WriteLine("region '" + LogMessageCodes_GeneratedCode + "' was not found");
				return res;
			}
			if(endPos == -1) {
				Console.WriteLine("pragma endregion was not found");
				return res;
			}

			for(int i = startPos + 1; i < endPos; i++) {
				enumFile.GoTo(i);
				EnumInfo info = new EnumInfo();
				info.ParseEnum(enumFile.LineText);
				res.Add(info);
				//Console.WriteLine("found enum value -> " + info.EnumName + " = " + info.Value);
			}

			startPos = msgInitFile.FindString(LogMessagesProvider_InitializeLogMessageText_GeneratedCode);
			endPos = msgInitFile.FindString("endregion");
			// this->LogMessageText[LogMessageCode::lmcSuccess] = "Some String";
			for(int i = startPos + 1; i < endPos; i++) { 
				msgInitFile.GoTo(i);
				string[] tokens = msgInitFile.LineText.Split(new string[] { "->", "=", ";", "[", "::", "]" }, StringSplitOptions.RemoveEmptyEntries);
				if(tokens.Length == 0)
					continue;
				for(int t = 0; t < tokens.Length; t++) {
					tokens[t] = tokens[t].Trim();
				}
				if(tokens[0] != "this" || tokens[1] != "m_logMessageText" || tokens[2] != "LogMessageCode") {
					Console.WriteLine("error: invalid enum initialization string " + msgInitFile.LineText);
					throw new ArgumentException();
				}
				EnumInfo info = GetEnum(res, tokens[3]);
				if(info == null) {
					throw new KeyNotFoundException("Enum initializer not found: '" + tokens[3] + "'  '" + res[0].EnumName + "'");
				}
				int messageStart = msgInitFile.LineText.IndexOf('"');
				int messageEnd = msgInitFile.LineText.LastIndexOf('"');
				if(messageStart == -1 || messageEnd == -1)
					throw new KeyNotFoundException("Enum message text not found: " + tokens[3]);
				info.MessageText = msgInitFile.LineText.Substring(messageStart + 1, messageEnd - messageStart - 1);
				//Console.WriteLine("found enum message text -> '" + info.MessageText + "' for enum " + tokens[3]);
			}

			return res;
		}

		public static EnumInfo GetEnum (List<EnumInfo> enums, string enumName) {
			return enums.FirstOrDefault(item => item.EnumName == enumName);
		}

		public static TextFile GetFileWithRegion (string regionName, List<TextFile> files) {
			foreach(TextFile file in files) {
				//Console.WriteLine("processing file " + file.FileName + " for region " + regionName);
				file.GoTo(0);
				if(file.FindString(regionName) != -1) {
					//Console.WriteLine("region '" + regionName + "' found in " + file.FileName + " line: " + file.Line);
					return file;
				}
			}
			return null;
		}

		public static List<TextFile> LoadSourceFiles () {
			List<string> files = GetSourceFiles();
			List<TextFile> loadedFiles = new List<TextFile>();
			foreach(string fileName in files) {
				TextFile lf = new TextFile();
				if(!lf.LoadFromFile(fileName)) {
					Console.WriteLine("error: loading file " + fileName);
					return null;
				}
				loadedFiles.Add(lf);
			}
			return loadedFiles;
		}

		public static List<string> GetSourceFiles () {
			List<string> sources = new List<string>();
			string sourceDir = "";
			if(!m_params.TryGetValue("s", out sourceDir)) {
				sourceDir = "../../source/";
				Console.WriteLine("Using default source directory: " + sourceDir);
			}
			GetSourceFiles(sourceDir, sources);
			return sources;
		}

		public static void GetSourceFiles (string path, List<string> sources) {
			IEnumerable<string> dirs = Directory.EnumerateDirectories(path);
			IEnumerable<string> files = Directory.EnumerateFiles(path);
			foreach(string fileName in files) {
				if(fileName.EndsWith(".h") ||
				   fileName.EndsWith(".hpp") ||
				   fileName.EndsWith(".cpp") ||
				   fileName.EndsWith(".c"))
					sources.Add(fileName);
			}
			foreach(string dir in dirs) {
				GetSourceFiles(dir, sources);
			}
		}

		static string FastServerConfigurationFile { get; set; }
		public static bool CopyFastServerConfigurationFile () { 
			string fileName = "";
			if(!m_params.TryGetValue("ax", out fileName)) {
				fileName = "asts_config_test.xml";
				Console.WriteLine("Using default XML config: " + fileName);
			}
			string inputPath = "";
			if(!m_params.TryGetValue("d", out inputPath)) {
				inputPath = "../../test/data/";
				Console.WriteLine("Using default data directory: " + inputPath);
			}
			string outputPath = "";
			if(!m_params.TryGetValue("o", out outputPath)) {
				outputPath = "/tmp/";
				Console.WriteLine("Using default output directory: " + outputPath);
			}
			if(File.Exists(outputPath + fileName)) {
				Console.WriteLine("found FAST server configuration file in destination. remove.");
				File.Delete(outputPath + fileName);
			}
			if(File.Exists(inputPath + fileName)) { 
				Console.WriteLine("copy FAST server test configuration file");
				File.Copy(inputPath + fileName, outputPath + fileName);
				FastServerConfigurationFile = outputPath + fileName;
				return true;
			} else {
				Console.WriteLine("error: file " + inputPath + fileName + " does not exist");
				return false;
			}
		}
	}
}
