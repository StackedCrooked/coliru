class NodeManagerService
{
    // the private factory class. This class will have access to the private
    // members of NodeManagerService because it is an inner class thereof
    struct NodeFactory
    {
        NodeFactory(NodeManagerService& nms) : m_nms(nms) { }

        // this is the factory method used by the NodeMObj::Manager to 
        //instantiate NodeMObj instances from cfgdb query results
        boost::shared_ptr<Node> operator()(cfgdb::NameValueList::Ptr nvl)
        {
            return boost::make_shared<NodeMObj>(nvl, m_nms.m_pFooMgr, 
                m_nms.m_pBarMgr, m_nms.m_pBazMgr, m_nms.m_pQuxMgr, 
                m_nms.m_pQuuxMgr, m_nms.m_pCorgeMgr, m_nms.m_pGraultMgr,
                m_nms.m_pGarplyMgr, m_nms.m_pWaldoManager, m_nms.m_pWaldoMgr);
        }

        NodeManagerService& m_nms;
    };
    
    
public:

    NodeManagerService() :
        /* omitted: setting up all the table pointers */
        m_pFooMgr(mostore.getManager<FooMObj>(...)),
        m_pBarMgr(mostore.getManager<BarMObj>(...)),
        m_pBazMgr(mostore.getManager<BazMObj>(...)),
        m_pQuxMgr(mostore.getManager<QuxMObj>(...)),
        m_pQuuxMgr(mostore.getManager<QuuxMObj>(...)),
        m_pCorgeMgr(mostore.getManager<CorgeMObj>(...)),
        m_pGraultMgr(mostore.getManager<GraultMObj>(...)),
        m_pGarplyMgr(mostore.getManager<GarplyMObj>(...)),
        m_pWaldoMgr(mostore.getManager<WaldoMObj>(...)),
        m_pFredMgr(mostore.getManager<FredMObj>(...)),
        m_pNodeManager(mostore.getManager<NodeMObj>(someTablePtr, NodeFactory(*this)) // No bind, the NodeFactory takes the place of the bind expression
    {
    }
        
  
private:
    FooMObj::Manager::Ptr m_pFooMgr;
    BarMObj::Manager::Ptr m_pBarMgr;
    BazMObj::Manager::Ptr m_pBazMgr;
    QuxMObj::Manager::Ptr m_pQuxMgr;
    QuuxMObj::Manager::Ptr m_pQuuxMgr;
    CorgeMObj::Manager::Ptr m_pCorgeMgr;
    GraultMObj::Manager::Ptr m_pGraultMgr;
    GarplyMObj::Manager::Ptr m_pGarplyMgr;
    WaldoMObj::Manager::Ptr m_pWaldoMgr;
    FredMObj::Manager::Ptr m_pFredMgr;
    NodeMObj::Manager::Ptr m_pNodeManager // <- the troublemaker, depends on all of the above mgrs
};
