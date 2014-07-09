
void OnesComplementSum(const uint8_t * inData, int inLength, uint32_t& sum)
{
    const uint16_t * data = reinterpret_cast<const uint16_t *>(inData);

    uint32_t a[4] = { 0, 0, 0, 0 };
    while ((inLength -= 8) >= 0)
    {
        a[0] += data[0];
        a[1] += data[1];
        a[2] += data[2];
        a[3] += data[3];
        data += 4;
    }

    sum += a[0];
    sum += a[1];
    sum += a[2];
    sum += a[3];

    inLength += 8;


    Reduce(sum);


    while ((inLength -= 2) >= 0)
    {
        sum += *data++;
    }

    if (inLength == -1)
    {
        // --- Add the last byte
        sum += static_cast<uint16_t>(*(reinterpret_cast<const uint8_t *>(data)));
    }

    Reduce(sum);

}

