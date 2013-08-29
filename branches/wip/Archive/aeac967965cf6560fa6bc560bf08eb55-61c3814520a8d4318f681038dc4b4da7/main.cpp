void FileSystemWatcherUser::ThreadedScan() {
	threaddone = false;
	while ( true ) {
		UpdateWatches();
        // If there's nothing left, destroy the thread: no reason
        // for it to be alive if there's no watchers alive
		if ( activewatches.size() < 1 ) {
			break;
		}
		else {
			TLockGuard guard ( scanmutex );
			/*for ( auto& drivekv : drives ) {
				ScanDrives( drivekv.first, std::get<0>( drivekv.second ), std::get<1>( drivekv.second ) );
			}*/
			for ( auto& watch : activewatches ) {
				watch->Scan();
			}
		}
	}
	threaddone = true;
}

void FileSystemWatcherUser::UpdateWatches() {
	// A std::atomic<bool> for when new objects are constructed or destructed
    // helps us not to over-lock and slow things down
    if ( !changes )
	    return;

	std::vector<FileSystemWatcherUser*> add; std::vector<FileSystemWatcherUser::Removal> remove; 
	{
		TLockGuard guard( pendingmutex );
		add = std::move( pendingadditions );
		remove = std::move( pendingremovals );
		pendingremovals.clear();
		pendingadditions.clear();
	}

	{
		TLockGuard scanguard( scanmutex );
		for ( auto&& addition : add ) {
			auto drivecatch = drives.find( addition->drive );
			if ( drivecatch == drives.end( ) ) {
				drives.emplace( addition->drive, std::make_tuple<ptr<void, ReleaseHandle>, ptr<void, ReleaseHandle>, lword>( null, null, 1 ) );
			}
			else {
				++std::get<2>( drivecatch->second );
			}
			activewatches.emplace_back( addition );
		}

		for ( auto&& removal : remove ) {
			auto drivecatch = drives.find( removal.drive );
			if ( drivecatch != drives.end( ) ) {
				--std::get<2>( drivecatch->second );
				if ( std::get<2>( drivecatch->second ) < 1 )
					drives.erase( drivecatch );
			}
			activewatches.erase( std::find( activewatches.begin(), activewatches.end(), removal.destructedelement ) );
		}
	}
	changes = false;
}