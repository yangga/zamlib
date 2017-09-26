//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_QVECTOR_H
#define ZAMLIB_QVECTOR_H

#include <vector>

namespace zam {
    namespace base {
        namespace container {

            template<class _T>
            class qvector {
            public:
                using value_type = _T;
                using container_type = std::vector<value_type>;
                using iterator = typename container_type::iterator;
                using const_iterator = typename container_type::const_iterator;
                using reverse_iterator = typename container_type::reverse_iterator;
                using const_reverse_iterator = typename container_type::const_reverse_iterator;
                using reference = typename container_type::reference;
                using compare_type = int (*)(void const *, void const *);
                using search_type = iterator(*)(iterator, iterator, const value_type &);
                using const_search_type = const_iterator(*)(const_iterator, const_iterator, const value_type &);

            public:
                container_type const &container() const { return cont_; }

                void clear() { cont_.clear(); }

                bool empty() const { return cont_.empty(); }

                size_t size() const { return cont_.size(); }

                iterator begin() { return cont_.begin(); }

                const_iterator begin() const { return cont_.cbegin(); }

                iterator end() { return cont_.end(); }

                const_iterator end() const { return cont_.cend(); }

                const_iterator cbegin() const { return cont_.cbegin(); }

                const_iterator cend() const { return cont_.cend(); }

                reverse_iterator rbegin() { return cont_.rbegin(); }

                reverse_iterator rend() { return cont_.rend(); }

                const_reverse_iterator crbegin() const { return cont_.crbegin(); }

                const_reverse_iterator crend() const { return cont_.crend(); }

                reference back() { return cont_.back(); }

                reference front() { return cont_.front(); }

                iterator find(value_type const &element) {
                    return QSearch(cont_, element);
                }

                const_iterator find(value_type const &element) const {
                    return QSearch(cont_, element);
                }

                void erase(const value_type &_Val) {
                    auto itr = find(_Val);
                    if (end() != itr) {
                        cont_.erase(itr);
                        sort();
                    }
                }

                void push(value_type &&_Val) {
                    cont_.push_back(std::forward<value_type>(_Val));
                    sort();
                }

                void push(const value_type &_Val) {
                    cont_.push_back(std::forward<const value_type>(_Val));
                    sort();
                }

                template<class... _Valty>
                void emplace(_Valty &&... _Val) {
                    cont_.emplace_back(std::forward<_Valty>(_Val)...);
                    sort();
                }

                void sort() {
                    if (cont_.size() <= 1)
                        return;

                    qvector::QSort(cont_);
                }

                value_type &operator[](const size_t index) {
                    return cont_[index];
                }

                value_type const &operator[](const size_t index) const {
                    return cont_[index];
                }

            public:
                static inline iterator
                QSearch(container_type &cont, value_type const &element, search_type searcher = std::lower_bound) {
                    auto itr = searcher(std::begin(cont), std::end(cont), element);
                    if (itr != cont.end() && !(element < *itr))
                        return itr;

                    return cont.end();
                }

                static inline const_iterator QSearch(container_type const &cont, value_type const &element,
                                                     const_search_type searcher = std::lower_bound) {
                    auto itr = searcher(std::begin(cont), std::end(cont), element);
                    if (itr != cont.end() && !(element < *itr))
                        return itr;

                    return cont.end();
                }

                static inline void
                QSort(container_type &cont, compare_type comp = qvectorCompare) {
                    std::qsort(static_cast<void *>(&cont.at(0)), cont.size(), sizeof(value_type), comp);
                }

            private:

                static inline int qvectorCompare(void const *pElem1, void const *pElem2) {
                    if (*static_cast<value_type const *>(pElem1) < *static_cast<value_type const *>(pElem2))
                        return -1;
                    if (*static_cast<value_type const *>(pElem1) == *static_cast<value_type const *>(pElem2))
                        return 0;

                    return 1;
                }

            private:
                container_type cont_;
            };
        }
    }
}

#endif //ZAMLIB_QVECTOR_H
