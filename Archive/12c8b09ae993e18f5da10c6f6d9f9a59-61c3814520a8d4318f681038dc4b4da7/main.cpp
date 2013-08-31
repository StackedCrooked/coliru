void FileSystemMonitor::UpdatePending ( ) {
	if ( !changes )
		return;

	std::vector<FileSystemMonitor*> add; 
	std::vector<FileSystemMonitor::Removal> remove; 
	{
		TLockGuard guard( pendingmutex );
		add = std::move( pendingadditions );
		remove = std::move( pendingremovals );
		pendingremovals.clear();
		pendingadditions.clear();
	}

	changes = false;

	{
		TLockGuard scanguard( scanmutex );
		for ( auto& addition : add ) {
			auto drivecatch = drives.find( addition->drive );
			if ( drivecatch == drives.end( ) ) {
				drives.emplace( addition->drive, std::make_pair<ptr<FileSystemMonitor>, lword>( new FileSystemMonitor( true, addition->drive ), 1 ) );
			}
			else {
				++drivecatch->second.second;
			}
			activelist.emplace_back( addition );
		}

		for ( auto& removal : remove ) {
			auto drivecatch = drives.find( removal.drive );
			if ( drivecatch != drives.end( ) ) {
				--drivecatch->second.second;
				if ( drivecatch->second.second < 1 )
					drives.erase( drivecatch );
			}
			activelist.erase( std::find( activelist.begin(), activelist.end(), removal.destructedelement ) );
		}
	}
}