void PostToMain(const std::function<void()> & inCallback)
{
    struct PostEvent : QEvent
    {
        static QEvent::Type GetType() { return static_cast<QEvent::Type>(QEvent::User + 1); }
 
        PostEvent(const std::function<void()> & inCallback) :
            QEvent(GetType()),
            mCallback(inCallback)
        {
        }
 
        std::function<void()> mCallback;
    };
 
    static struct : QObject
    {
        bool event(QEvent * ev)
        {
            if (PostEvent * post = dynamic_cast<PostEvent*>(ev))
            {
                post->mCallback();
                return true;
            }
            return QObject::event(ev);
        }
 
    } fReceiver;
 
    qApp->postEvent(&fReceiver, new PostEvent(inCallback));
}