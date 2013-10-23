/*
 * PacketParser.h
 *
 * Created: 10/2/2013 15:25:05
 *  Author: Ehsan Khodadad, Mona Ghodsi
 */ 


#ifndef PACKETPARSER_H_
#define PACKETPARSER_H_


#define SOH 1
#define STX 2
#define ETX 3
#define ACK 6
#define NULL '\0'
typedef enum {bpsSOH,
/* bpsHeaderSpace1, bpsHeaderChar1, bpsHeaderChar2, bpsHeaderChar3, bpsHeaderSpace2, */ 
    						bpsSTX,
							bpsETX, 
							bpsBCC} TBodyPaserStatus;


typedef enum {imtRead, 
							imtWrite, 
							imtExe} TInternalMessageType;

/**
* \defgroup document the members of an enum
*/
/**@{*/
  /** \typedef to document a type definition. An enum type.
  * The documentation block cannot be put after the enum!
  */	
typedef enum { mpsAsterisk,
							 mpsEqualSign,
							 mpsVersionMessage, 
							 mpsCmd, 
							 mpsModemUid, 
							 mpsMeterUid, 
							 mpsDestSourceUid,
							 mpsMessageId1, 
							 mpsMessageId2, 
							 mpsSimCharge, 
							 mpsRes1, 
							 mpsBody, 
							 mpsFinishSymbol,
							 mpsHeaderCollector, //This section has a permanent length
							 mpsBodyCollector // This section has variable length
							 } TMessageParserStatus;
  /**@}*/
#define StartSymbolSecLen 2
#define VersionMessageSecLen 2
#define CmdSectionLen 1
#define ModemUidSecLen 8
#define MeterUidSecLen 8
#define DestSourceSecLen 2
#define MessageId1SecLen 2
#define MessageId2SenLen 1
#define SimChargeSecLen 2
#define Reserved1SecLen 4
#define HeaderLen (StartSymbolSecLen + VersionMessageSecLen + CmdSectionLen + ModemUidSecLen + MeterUidSecLen + DestSourceSecLen + MessageId1SecLen + MessageId2SenLen + SimChargeSecLen + Reserved1SecLen) 
#define rsaPacketBodyLength 127
#define PacketLen 160


#define StartSymbolSecOffset 0
#define VersionMessageSecOffset StartSymbolSecOffset+StartSymbolSecLen
#define CmdSectionSecOffset VersionMessageSecOffset+VersionMessageSecLen
#define ModemUidSecOffset CmdSectionSecOffset+CmdSectionLen
#define MeterUidSecOffset ModemUidSecOffset+ModemUidSecLen
#define DestSourceSecOffset MeterUidSecOffset+MeterUidSecLen
#define MessageId1SecOffset DestSourceSecOffset+DestSourceSecLen
#define MessageId2SecOffset MessageId1SecOffset+MessageId1SecLen
#define SimChargeSecOffset MessageId2SecOffset+MessageId2SenLen
#define Reserved1SecOffset SimChargeSecOffset+SimChargeSecLen
#define BodyOffset Reserved1SecOffset+Reserved1SecLen


#define HexCharactersCondition(input) (	((input > '0') && (input < '9')) || \
						                            ((input > 'a') && (input < 'f')) || \
																				((input > 'A') && (input < 'F'))    \
																			)
						 
#define DecCharactersCondition(input) ((input > '0') && (input < '9'))

#define MessageObisSection_MaxLen 25




//::from behnam's code
typedef enum {
	//valid codes from 1
	rsobtcUnknown, rsobtcNoCode, rsobtcATC, rsobtcMD, rsobtcP0, rsobtcP1, rsobtcP1MD, rsobtcPAMD, rsobtcR5, rsobtcRMD, rsobtcW5, rsobtcWMD
} TRSOBISTypeCode;

typedef enum {
	obsStart, obsType, obsCode, obsData, obsETX, obsBCC, obsIdentifier, obsIdentCR, obsAcknowledge, obsIgnoring,
} TOBISStates;

typedef enum {
	obrNoAnswer, obrSOHDetected, obrDataNoBCC, obrDataCorrectBCC, obrIdentifier, obrAcknowledge, obrDataWrongBCC, obrWrongPacket,
} TOBISResults;//

typedef enum {
	rsapsInvalid, rsapsPacketCompGPRS, rsapsPacketCompSMS, rsapsWrongOBIS, rsapsWaitForSendGPRS, rsapsWaitForSendSMS
} TRSAPacketStatus;


#define rsobtListSize 11




typedef struct {
	char RAW[rsaPacketBodyLength+2];
	char RAWResult[rsaPacketBodyLength+2];
	char RAWResultLength;
	TRSOBISTypeCode Type; // could be W5, R5, ...
	char Code[15];        // include 5 part of 2 char hex and 4 dot as separator
	char Data[75];        // data part is between parenthesis.
	TOBISStates State;
	TOBISResults Result;
	char BCC;
	char TmpStr[10];
	char TmpStrIndex;
	char * RawBuf;
	char RawBufIndex;
} TRSAOBISPack;


typedef struct {
	char StartSymbol[2];      // always '*='
	char MessageVersion[2];   // always '51'
	char CMD;                 // or Packet type, K, J, Z, ...
	char ModemUID[ModemUidSecLen];         //
	char MeterUID[MeterUidSecLen];         // default is 'FFFFFFFF'
	char DSUID[DestSourceSecLen];            // just return as it is
	char MessageID[MessageId1SecLen];        // just return as it is for now
	char MessageIndex;        // need to increment in multi message return.
	char SimCharge[SimChargeSecLen];
	char Reserved[Reserved1SecLen];         // Always 'FFFFFF'
	char Body[rsaPacketBodyLength]; // the OBIS code formatted body
	//char CRC[4];              // Always 'FFFF' for now
	char FinishSymbol;        // Always '#'
	char Terminator;          // Always NULL for printing purposes
	TRSAPacketStatus Status;  // Current status of structure.
	TRSAPacketStatus LastStatus;  // status of structure back up, use in multi answer messages.
	unsigned int StatusTimeOut;
	char MultiReplyLastSource;
	
	char BodyResultIndex;
	char MeterResultIndex;
	char CommandsIndex;
	char BodyCommandsCopy[rsaPacketBodyLength+1];
	char CommandResult[rsaPacketBodyLength+1];
	TRSAOBISPack OBIS;
	char CommandCode;
	char ValidUID;
} TRSAPacketFormat;
#endif /* PACKETPARSER_H_ */



