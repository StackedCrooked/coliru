    template< typename F > void log(ChannelColors destinationChannel, F message_creator)
    {
    if (fileLogOpen[static_cast<int>(destinationChannel)]){
	    fileStreams[static_cast<int>(destinationChannel)] << message_creator() << std::endl;
	}
	else if(windowLogOpen[static_cast<int>(destinationChannel)]){
	    Gui::getSingleton().getWindowLogger(destinationChannel)->appendText(F());

	}
    }
    
    // Somewhere in the code I call 
    ChannelDebug::getSingletonPtr()->log(ChannelColors::blue, [&](){ std::stringstream ss; 
    ss << (xxLeft  >> mPrecisionDigits )<< " " << (xxLeftOld  >> mPrecisionDigits )<< " " << (xxRight  >> mPrecisionDigits )<< " " << (xxRightOld  >> mPrecisionDigits )<< " " <<endl ;
    return ss.str(); });
    // I get
    
    
    /home/tom/Opendungeons/opendungeons/source/CullingManager.cpp:266:287:   required from here
    /home/tom/Opendungeons/opendungeons/source/ChannelDebug.h:33:6: error: use of deleted function ‘CullingManager::newBashAndSplashTiles(int64_t)::__lambda0::<lambda>()’
      Gui::getSingleton().getWindowLogger(destinationChannel)->appendText(F());