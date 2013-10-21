int doItAll( )
{
  screen->print( "Initialse" );
  Clss_CoreInit_Entry( );
  
  int retval = 0;
  
  unsigned char UID[ 15 ] =  { 0 };
  unsigned char SAK[ 256 ] =  { 0 };
  unsigned char rats[ 256 ] =  { 0 };
  
  unsigned char kernType = 0;
  unsigned char aid[ 20 ] =  { 0 };
  int length = 0;
  
  unsigned char AID[ ][ 8 ] = { { "\xA0\x00\x00\x00\x03\x10\x10" } };
  
  // ###############################
  // Set Preliminary Processing Info
  // ###############################
  Clss_PreProcInfo cppi;
  memset( &cppi, 0, sizeof ( cppi ) );
  
  cppi.ucCrypto17Flg = 1;
  cppi.ucZeroAmtNoAllowed = 0;
  cppi.ucStatusCheckFlg = 0;
  memcpy( cppi.aucReaderTTQ, "\xA0\x00\x00\x00", 4 );
  
  cppi.ucRdClssTxnLmtFlg = 1;
  cppi.ulRdClssTxnLmt = 10000;
  
  cppi.ucTermFLmtFlg = 1;
  cppi.ulTermFLmt = 8000;
  cppi.ucRdClssFLmtFlg = 1;
  cppi.ulRdClssFLmt = 8000;
  cppi.ucRdCVMLmtFlg = 1;
  cppi.ulRdCVMLmt = 6000;
  
  screen->print( "Add AID" );
  for ( int i = 0; i < 1; ++i )
  {
    retval = Clss_AddAidList_Entry( ( unsigned char* )AID[ i ], 7, PART_MATCH, KERNTYPE_DEF );
    if ( retval != EMV_OK )
    {
      return retval + 100000;
    }
    
    memcpy( cppi.aucAID, AID[ i ], 7 );
    cppi.ucAidLen = 7;
    
    retval = Clss_SetPreProcInfo_Entry( &cppi );
    if ( retval != EMV_OK )
    {
      return retval + 200000;
    }
  }
  
  // ##############################
  // Perform Preliminary Processing
  // ##############################
  Clss_TransParam ctp;
  memcpy( ctp.aucTransDate, "\x13\x10\x21\x00", 5 );
  memcpy( ctp.aucTransTime, "\x16\x10\x40\x00", 5 );
  ctp.ulTransNo = 0x00;
  ctp.ucTransType = 0x00;
  ctp.ulAmntAuth = 100;
  ctp.ulAmntOther = 0;
  
  screen->print( "PreTransProc" );
  Clss_PreTransProc_Entry( &ctp );
  
  // ###############
  // Prompt for card
  // ###############
  retval = -1;
  OsPiccOpen(  );
  while ( retval != 0 )
  {
    retval = OsPiccPoll( &type, atq );
  }

  // ##############
  // Anti collision
  // ##############
  retval = OsPiccAntiSel( type, UID, atq[ 0 ], SAK );
  
  if ( retval != EMV_OK )
  {
    return retval + 300000;
  }

  // #############
  // Activate Card
  // #############
  retval = OsPiccActive( type, rats );
  
  if ( retval != EMV_OK )
  {
    return retval + 400000;
  }
  
  // ##################
  // Select application
  // ##################
  retval = Clss_AppSlt_Entry( 0, 0 ); // Fails with EMV_NO_APP_PPSE_ERR
  
  if ( retval != EMV_OK )
  {
    return retval + 500000;
  }

  // #################
  // Final application
  // #################
  retval = Clss_FinalSelect_Entry( &kernType, aid, &length );
  
  if ( retval != EMV_OK )
  {
    return retval + 600000;
  }

  GetKey(  );
}