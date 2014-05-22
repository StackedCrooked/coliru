message PbMessage {
    enum Type {
		LIST    = 1;
		INT32   = 2;
		INT64   = 3;
		FLOAT   = 4;
		STRING  = 5;
	};

	required Type      type = 1;
	repeated PbMessage list = 2;
	optional int32     int32Value = 3;
	optional int64     int64Value = 4;
	optional float     floatValue = 5;
	optional string    stringValue = 6;
}
