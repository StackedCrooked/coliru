
void MainWindow::repairSelection_HACK()
{
    std::weak_ptr<MainWindow> weak_self(mSelf);
    auto selection = mCollection.selection();

    std::thread([=]{
        // ELABORATE AND DIRTY HACK
        // TODO: UNDERSTAND INSTEAD OF HACK

        // run a for-loop which repeatedly re-selects the required
        // do this 10 times over a period of 500 milliseconds
        for (int i = 0; i != 10; ++i) {
            PostToMain([=]{
                if (weak_self.expired()) {
                    return;
                }
                mCollection.select(selection);
                listView().setCurrentIndex(listModel().index(mCollection.selectedIndex(), 0));
                listView().scrollTo(listView().currentIndex(), ListView::PositionAtTop);
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }).detach();
}
