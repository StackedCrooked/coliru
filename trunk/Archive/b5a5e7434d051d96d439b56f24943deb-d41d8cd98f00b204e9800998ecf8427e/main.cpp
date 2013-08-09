

boost::optional<SegmentInfo> SACK_nextSeg(uint32_t inNumDupacks, uint32_t inCWND)
{
    if (auto result = SACK_nextSeg_1(inNumDupacks))
    {
        return result;
    }

    if (auto result = SACK_nextSeg_2(inCWND))
    {
        return result;
    }

    if (auto result = SACK_nextSeg_3())
    {
        return result;
    }

    return boost::none;
}