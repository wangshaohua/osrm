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

#ifndef EDGE_H
#define EDGE_H

#include <cassert>

class Edge
{
public:

    bool operator< (const Edge& e) const {
        if (source() == e.source()) {
            if (target() == e.target()) {
                if (weight() == e.weight()) {
                    return (isForward() && isBackward() &&
                            ((! e.isForward()) || (! e.isBackward())));
                }
                return (weight() < e.weight());
            }
            return (target() < e.target());
        }
        return (source() < e.source());
    }

    /** Default constructor. target and weight are set to 0.*/
    Edge() :
        _source(0), _target(0), _name(0), _weight(0), forward(0), backward(0), _type(0) { assert(false); } //shall not be used.

    explicit Edge(NodeID s, NodeID t, NodeID n, EdgeWeight w, bool f, bool b, short ty) :
            _source(s), _target(t), _name(n), _weight(w), forward(f), backward(b), _type(ty) { assert(ty >= 0); }

    NodeID target() const {return _target; }
    NodeID source() const {return _source; }
    NodeID name() const { return _name; }
    EdgeWeight weight() const {return _weight; }

    short type() const { assert(_type >= 0); return _type; }
    bool isBackward() const { return backward; }
    bool isForward() const { return forward; }
    bool isLocatable() const { return _type != 14; }

    NodeID _source;
    NodeID _target;
    NodeID _name:31;
    EdgeWeight _weight:31;
    bool forward:1;
    bool backward:1;
    short _type;
};

struct MinimalEdgeData
{
public:
    EdgeWeight distance;
    bool forward;
    bool backward;
};

typedef Edge ImportEdge;

#endif // EDGE_H
