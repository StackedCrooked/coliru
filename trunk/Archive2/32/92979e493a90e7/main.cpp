#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

using Position = boost::tuple<int,int,int>;

struct CTileFigure {
    Position m_Pos { 0, 0, 0 };
};

struct CFigureObject {
    bool m_IsPlacedOnMap = true;
    boost::shared_ptr<CTileFigure> m_pTileFigure { new CTileFigure };
};

struct CArmyCard {
    boost::ptr_list<CFigureObject> GetFiguresList() { return m_FiguresList; }
    boost::ptr_list<CFigureObject> m_FiguresList;
};

struct CPlayer {
    boost::ptr_list<CArmyCard> m_ArmyList;
};

struct CGameDoc {
    boost::optional<CFigureObject&> GetFigureAtPos(Position);

    boost::ptr_vector<CPlayer> m_PlayerArray;
};

boost::optional<CFigureObject&> CGameDoc::GetFigureAtPos(Position position) {

    for (auto &player   : m_PlayerArray)
    for (auto &armyCard : player.m_ArmyList)
    for (auto &figure   : armyCard.GetFiguresList())
        if (figure.m_IsPlacedOnMap && figure.m_pTileFigure->m_Pos == position)
            return figure;

    return boost::none;
}

int main() { }
