int main() {
    //display the context menu at pos in screen coordinates instead of widget coordinates of the content of the currently focused table
    nodeContextMenu.exec((activeNodeTable->hasFocus() ? activeNodeTable : nodeTable)->viewport()->mapToGlobal(pos));
    
    
    auto focusedTable = activeNodeTable->hasFocus() ? activeNodeTable : nodeTable;
    nodeContextMenu.exec(focusedTable->viewport()->mapToGlobal(pos));
    
    
    auto focusedTable = nodeTable;
    if (activeNodeTable->hasFocus()) {
        focusedNodeTable = activeNodeTable;
    }
    nodeContextMenu.exec(focusedTable->viewport()->mapToGlobal(pos));
    
    
    if (activeNodeTable->hasFocus()) {
        pos = activeNodeTable->viewport()->mapToGlobal(pos);
    } else {
        pos = nodeTable->viewport()->mapToGlobal(pos);
    }
    nodeContextMenu.exec(pos);
    
    
    auto pos = nodeTable->viewport()->mapToGlobal(pos);
    if (activeNodeTable->hasFocus()) {
        pos = activeNodeTable->viewport()->mapToGlobal(pos);
    }
    nodeContextMenu.exec(pos);
    
    
    if (activeNodeTable->hasFocus()) {
        nodeContextMenu.exec(activeNodeTable->viewport()->mapToGlobal(pos));
    } else {
        nodeContextMenu.exec(nodeTable->viewport()->mapToGlobal(pos));
    }
}
