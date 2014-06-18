#include <cstdio>
#include <memory>

/*********************************************************************
 * JRN
 * NOTICE: THIS IS BETA CODE.
 ********************************************************************/

class TimerEvent
{
    protected:
		int m_eventData;
		int m_frequencyMS;

	public:
		TimerEvent( int data ) : m_eventData( data ) {}
		virtual bool HandleEvent() = 0;
		virtual ~TimerEvent();
};


class Timer
{
	private:
		std::shared_ptr<TimerEvent> m_ptr_Evt;
	
	public:
		Timer( std::shared_ptr<TimerEvent> ptr_Evt );
		~Timer();
};


Timer::Timer( std::shared_ptr<TimerEvent> ptr_Evt ) : m_ptr_Evt( ptr_Evt )
{
	m_ptr_Evt->HandleEvent();
}

Timer::~Timer()
{
	printf( "Timer Destructor\n" );
}


class SecondHandler : public virtual TimerEvent
{
	public:
		SecondHandler( int data ) : TimerEvent( data ) {}
		virtual bool HandleEvent();
};

bool SecondHandler::HandleEvent()
{
	printf("In SecondHandler::HandleEvent() %d\n", m_eventData);
	return( true );
}


SecondHandler::TimerEvent::~TimerEvent()
{
	printf("TimerEvent being destructed\n");
}


int main( int argc, char *argv[] )
{
	Timer SecondTimer( std::shared_ptr<TimerEvent>( new SecondHandler( 2 ) ));
	return( 0 );
}
