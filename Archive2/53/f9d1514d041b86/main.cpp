#include "QtCore"


// Post a function object on the event loop (from a different thread).
void PostToMain(const std::function<void()> & task)
{
    struct PostEvent : QEvent
    {
        static QEvent::Type GetType() { return static_cast<QEvent::Type>(QEvent::User + 1); }

        PostEvent(const std::function<void()> & task) :
            QEvent(GetType()),
            mCallback(task)
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

    // thread-safe
    qApp->postEvent(&fReceiver, new PostEvent(task));
}
