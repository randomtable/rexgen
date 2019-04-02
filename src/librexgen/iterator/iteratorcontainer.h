/*
  rexgen - a tool to create words based on regular expressions
  Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/


#ifndef SRC_LIBREXGEN_ITERATOR_ITERATORCONTAINER_H_
#define SRC_LIBREXGEN_ITERATOR_ITERATORCONTAINER_H_

#include <librexgen/iterator/iterator.h>
#include <vector>
#include <memory>

#ifdef __cplusplus
namespace rexgen {
  class IteratorState;

  class IteratorContainer : public Iterator {
  public:
    typedef std::vector<std::unique_ptr<Iterator>> children_list_type;

    virtual void updateAttributes(IteratorState& iterState) override {
      for (auto& child : iterators) {
        child->updateAttributes(iterState);
      }
    }

    virtual void updateReferences(IteratorState& iterState) override {
      for (auto& child : iterators) {
        child->updateReferences(iterState);
      }
    }

    virtual void addChild(std::unique_ptr<Iterator>&& i) {
      iterators.push_back(std::move(i));
    }

    virtual void addChild(Iterator&& iter) {
      iterators.push_back(iter);
    }

    inline children_list_type::value_type&
    operator[](size_t idx) { return iterators[idx]; }

    inline const children_list_type::value_type&
    operator[](size_t idx) const { return iterators[idx]; }

    inline children_list_type::value_type&
    at(size_t idx) { return iterators.at(idx); }

    inline const children_list_type::value_type&
    at(size_t idx) const { return iterators.at(idx); }

    children_list_type::iterator        begin()       {return iterators.begin(); }
    children_list_type::const_iterator  begin() const {return iterators.cbegin(); }
    children_list_type::const_iterator cbegin() const {return iterators.cbegin(); }
    children_list_type::iterator        end()         {return iterators.end(); }
    children_list_type::const_iterator  end()   const {return iterators.cend(); }
    children_list_type::const_iterator cend()   const {return iterators.cend(); }

  protected:
    void setPosition(children_list_type::iterator i) { iter = i; }

    void incrementPosition() { ++iter; }

    void resetPosition() { iter = iterators.begin(); }

    children_list_type::iterator       getPosition()       { return iter; }
    children_list_type::const_iterator getPosition() const { return iter; }

  private:
    children_list_type iterators;
    children_list_type::iterator iter;
  };
}
#endif /* __cplusplus */

#endif /* SRC_LIBREXGEN_ITERATOR_ITERATORCONTAINER_H_ */
