

InterProcessData::InterProcessData()
{
    shared_memory_object::remove("shared_memory");

    try
    {
        shm.reset(new shared_memory_object(create_only ,"shared_memory" ,read_write));
        shm->truncate(sizeof(Data));

        region.reset(new mapped_region(*shm, read_write));
        assert(sizeof(Data) == region->get_size());

        void * addr = region->get_address();

        data = new (addr) Data;
    }
    catch(interprocess_exception &ex)
    {
        shm.reset(new shared_memory_object(open_only ,"shared_memory" ,read_write));
        shm->truncate(sizeof(Data));

        region.reset(new mapped_region(*shm, read_write));
        assert(sizeof(Data) == region->get_size());

        data = static_cast<Data*>(region->get_address());
    }
}