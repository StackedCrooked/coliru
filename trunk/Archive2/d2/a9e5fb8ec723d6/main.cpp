    template< typename F > void log(ChannelColors destinationChannel, F message_creator)
    {
    if (fileLogOpen[static_cast<int>(destinationChannel)]){
	    fileStreams[static_cast<int>(destinationChannel)] << message_creator() << std::endl;
	}
	else if(windowLogOpen[static_cast<int>(destinationChannel)]){
	    Gui::getSingleton().getWindowLogger(destinationChannel)->appendText(F());

	}
    }