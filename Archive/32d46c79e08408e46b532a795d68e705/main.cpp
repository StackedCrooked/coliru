

RPC_MESSAGE(Stats,
            RPC_MEMBER(int64_t, txTotal)
            RPC_MEMBER(int64_t, rxTotal)
            RPC_MEMBER(int64_t, rxError)
            RPC_MEMBER(ResultCodeCounter, results)
            RPC_MEMBER(ExceptionCounter, exceptions))

BOOST_STRONG_TYPEDEF(uint64_t, TxTotal)
BOOST_STRONG_TYPEDEF(uint64_t, RxTotal)
BOOST_STRONG_TYPEDEF(uint64_t, RxError)

DEFINE_MESSAGE(Stats,
    (TxTotal)
    (RxTotal)
    (RxError));