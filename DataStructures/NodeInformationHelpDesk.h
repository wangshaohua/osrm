/*
    open source routing machine
    Copyright (C) Dennis Luxen, others 2010

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU AFFERO General Public License as published by
the Free Software Foundation; either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
or see http://www.gnu.org/licenses/agpl.txt.
*/

#ifndef KDTREE_H_
#define NODEINFORMATIONHELPDESK_H_

#include <omp.h>

#include <climits>
#include <cstdlib>

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include "../typedefs.h"

#include <kdtree++/kdtree.hpp>

typedef KDTree::KDTree<2, duplet, std::pointer_to_binary_function<duplet,int,double> > duplet_tree_type;

class NodeInformationHelpDesk{
public:
    ~NodeInformationHelpDesk();
    NodeInformationHelpDesk() { int2ExtNodeMap = new vector<NodeInfo>();}
    duplet_tree_type * initKDTree(ifstream& input);

    NodeID getExternalNodeID(const NodeID node);
    NodeInfo& getExternalNodeInfo(const NodeID node);
    int getLatitudeOfNode(const NodeID node);
    int getLongitudeOfNode(const NodeID node);

    NodeID getNumberOfNodes() const { return int2ExtNodeMap->size(); }

    inline NodeID findNearestNodeIDForLatLon(const int lat, const int lon, NodeCoords<NodeID> * data) const
    {

       duplet dup = *(kdtree->find_nearest(duplet(0, lat, lon)).first);
       data->id = dup.id;
       data->lat = dup.d[1];
       data->lon = dup.d[0];
       return data->id;
    }
private:
    vector<NodeInfo> * int2ExtNodeMap;
    duplet_tree_type * kdtree;
};

//////////////////
//implementation//
//////////////////

NodeInformationHelpDesk::~NodeInformationHelpDesk(){
    //	delete graph;
    //	delete calc;
    //	delete c;
}

/* @brief: initialize kd-tree and internal->external node id map
 *
 */
duplet_tree_type * NodeInformationHelpDesk::initKDTree(ifstream& in)
{
//    NodeID i = 0;
    while(!in.eof())
    {
        NodeInfo b;
        in.read((char *)&b, sizeof(b));
        int2ExtNodeMap->push_back(b);
       // i++;
    }
    in.close();

    duplet_tree_type * tree = new duplet_tree_type(std::ptr_fun(return_dup));
    NodeID id = 0;
    for(vector<NodeInfo>::iterator it = int2ExtNodeMap->begin(); it != int2ExtNodeMap->end(); it++)
    {
        duplet super_dupre(id, it->lat, it->lon);
        tree->insert(super_dupre);
        id++;
    }
    kdtree = tree;
    return tree;
}

NodeID NodeInformationHelpDesk::getExternalNodeID(const NodeID node)
{
//    google::dense_hash_map<NodeID, NodeInfo>::iterator temp = int2ExtNodeMap->find(node);
//    if(temp == int2ExtNodeMap->end())
//        return UINT_MAX;
//    return temp->second.id;
    return int2ExtNodeMap->at(node).id;
}

NodeInfo& NodeInformationHelpDesk::getExternalNodeInfo(const NodeID node)
{
    return int2ExtNodeMap->at(node);
}

int NodeInformationHelpDesk::getLatitudeOfNode(const NodeID node)
{
//    google::dense_hash_map<NodeID, NodeInfo>::iterator temp = int2ExtNodeMap->find(node);
//    if(temp == int2ExtNodeMap->end())
//        return UINT_MAX;
//    return temp->second.lat;
    return int2ExtNodeMap->at(node).lat;
}

int NodeInformationHelpDesk::getLongitudeOfNode(const NodeID node)
{
//    google::dense_hash_map<NodeID, NodeInfo>::iterator temp = int2ExtNodeMap->find(node);
//    if(temp == int2ExtNodeMap->end())
//        return UINT_MAX;
//    return temp->second.lon;
    return int2ExtNodeMap->at(node).lon;
}

#endif /*KDTREE_H_*/