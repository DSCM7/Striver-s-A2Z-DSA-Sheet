# C++ STL — Detailed Notes

> Reference notes covering the core STL containers, built for someone coming from **Python** and **C**.

---

## 0. The Big Picture

STL (Standard Template Library) has **4 components**:

1. **Containers** — data structures that store collections of objects (vector, set, map, stack, queue, etc.)
2. **Iterators** — objects that point to elements inside containers, used to traverse them (like generalized pointers)
3. **Algorithms** — pre-built functions that operate on containers via iterators (sort, find, reverse, etc.)
4. **Functors (Function objects)** — objects that behave like functions, often used to customize algorithm behavior (e.g. custom comparators)

### Container categories

| Type | Examples |
|---|---|
| Sequence containers | vector, list, deque, array |
| Associative containers | set, multiset, map, multimap |
| Unordered associative containers | unordered_set, unordered_map, unordered_multiset, unordered_multimap |
| Container adapters | stack, queue, priority_queue |

### Mental-model cheat sheet (Python/C → C++)

| Concept | Python | C | C++ STL |
|---|---|---|---|
| Dynamic array | `list` | manual malloc/realloc | `vector` |
| Unique, sorted collection | — | — | `set` |
| Unique, unordered collection | `set()` | — | `unordered_set` |
| Key-value, sorted by key | — | — | `map` |
| Key-value, unordered | `dict` | — | `unordered_map` |
| Doubly linked list | (`collections.deque` closest) | manual struct + pointers | `list` |
| LIFO stack | `list` used as stack | manual | `stack` |
| FIFO queue | `collections.deque` | manual | `queue` |
| Double-ended queue | `collections.deque` | manual | `deque` |
| Heap | `heapq` | manual | `priority_queue` |

**Big naming trap:** C++'s `list` is a **doubly linked list**, NOT a dynamic array. Python's `list` is what C++ calls `vector`.

---

## 1. `vector` — Dynamic Array

Grows/shrinks automatically, unlike a fixed C-style array. Equivalent to Python's `list`, restricted to one type.

### Declaration
```cpp
#include <vector>
vector<int> v;              // empty
vector<int> v(5);           // size 5, all 0
vector<int> v(5, 100);      // size 5, all 100
vector<int> v = {1, 2, 3};  // initializer list
vector<int> v2(v1);         // copy

vector<pair<int,int>> vp = {{1,2}, {3,4}};
vector<vector<int>> grid(3, vector<int>(4, 0)); // 3x4 grid of 0s
```

### Add / Remove
```cpp
v.push_back(10);              // insert at end — O(1) amortized
v.pop_back();                  // remove last — O(1)
v.insert(v.begin(), 5);        // insert at front — O(n)
v.insert(v.begin()+2, 3, 100); // insert 100, three times, at index 2
v.erase(v.begin());            // remove first — O(n)
v.erase(v.begin(), v.begin()+2); // remove range [0,2)
```

### Access
```cpp
v[i];        // no bounds checking
v.at(i);     // bounds checked (throws if out of range)
v.front();   // first element
v.back();    // last element
```

### Traversal
```cpp
v.begin();  v.end();     // forward iterators
v.rbegin(); v.rend();    // reverse iterators

for (auto it = v.begin(); it != v.end(); it++) cout << *it << " ";
for (auto x : v) cout << x << " ";   // range-based, simplest
```

### Size
```cpp
v.size();  v.empty();  v.clear();  v.resize(10);
```

### Internals (interview point)
Vector doesn't reallocate on every `push_back`. When capacity runs out, it typically **doubles capacity** (new block, copy elements, free old block). This is why `push_back` is **amortized O(1)** — most calls O(1), occasional O(n) reallocation, averages out.
```cpp
v.capacity();        // allocated capacity (may exceed size())
v.shrink_to_fit();   // request to shrink capacity to size()
```

---

## 2. `set` — Sorted Unique Elements

Stores **unique** elements, **always sorted**, implemented as a **balanced BST (Red-Black Tree)**. All ops are **O(log n)**.

Unlike Python's `set()` (hash-based, unordered), C++ `set` is always sorted.

```cpp
#include <set>
set<int> s;
s.insert(30); s.insert(10); s.insert(20); s.insert(10); // dup ignored
for (int x : s) cout << x << " ";   // 10 20 30 — sorted, unique
```

### Key functions
```cpp
s.insert(x);
s.erase(x);
s.count(x);      // 1 if exists, 0 if not
s.find(x);       // iterator to x, or s.end() if not found
s.size();  s.empty();
```

### Ordered queries — the superpower
```cpp
s.lower_bound(x);  // iterator to first element >= x
s.upper_bound(x);  // iterator to first element > x
```
```cpp
set<int> s = {10, 20, 30, 40};
auto it = s.lower_bound(25);  // -> 30
```
Python's `set()` cannot do this without extra sorted-list machinery.

**Use cases:** de-duplicate + sort a collection in one step (`set<int> s(v.begin(), v.end());`), nearest smaller/larger element queries.

---

## 3. `multiset` — Sorted, Duplicates Allowed

Same as `set`, but duplicates **are** allowed. Still auto-sorted.

```cpp
#include <set>
multiset<int> ms;
ms.insert(10); ms.insert(10); ms.insert(20);
for (int x : ms) cout << x << " ";   // 10 10 20
```

**Gotcha:** `ms.erase(x)` removes **ALL** occurrences of `x`.
```cpp
ms.erase(10);              // removes BOTH 10s
ms.erase(ms.find(10));     // removes just ONE instance
```

`ms.count(x)` now returns the actual number of occurrences (unlike `set`, where it's always 0/1).

Everything else (`insert`, `find`, `lower_bound`, `upper_bound`, `size`) behaves like `set`.

---

## 4. `unordered_set` — Hash-Based Unique Elements

Same as `set` (unique values) but:
- **No guaranteed order**
- Implemented as a **hash table**
- **O(1) average** ops (worst case O(n) on collisions)

This is the direct equivalent of Python's `set()`.

```cpp
#include <unordered_set>
unordered_set<int> us;
us.insert(30); us.insert(10); us.insert(20);
for (int x : us) cout << x << " ";  // order not guaranteed
```

### Decision table (set family)
| Need | Use |
|---|---|
| Fast, don't care about order | `unordered_set` — avg O(1) |
| Sorted / `lower_bound`-`upper_bound` queries | `set` — O(log n) |
| Duplicates + sorted | `multiset` |
| Duplicates + no order, fast | `unordered_multiset` |

**Gotcha:** `unordered_set`'s O(1) is *average case only*. Worst case (hash collisions) degrades to O(n) — in competitive programming, this container can be deliberately "hacked" into worst-case behavior. `set` is always guaranteed O(log n).

---

## 5. `map` — Sorted Key → Value Pairs

Stores unique **key → value** pairs, sorted by key. Implemented as balanced BST. C++'s answer to Python's `dict`, except always sorted by key.

```cpp
#include <map>
map<string, int> mp;
mp["apple"] = 5; mp["banana"] = 2; mp["cherry"] = 8;
for (auto p : mp) cout << p.first << " " << p.second << endl;
// sorted alphabetically by key
```

### Elements are `pair<K, V>`
```cpp
pair<string,int> p = {"apple", 5};
p.first;   // "apple"
p.second;  // 5
```

### Key functions
```cpp
mp["apple"];        // access; CREATES key with value 0 if missing!
mp.at("apple");      // access; throws if missing (safer)
mp.erase("apple");
mp.count("apple");   // 1 or 0
mp.find("apple");    // iterator, or mp.end()
mp.size();
```

**Major gotcha:** Using `mp["key"]` just to *check* existence silently **inserts** that key with default value.
```cpp
if (mp["banana"] == 5) { }        // BUG — inserts "banana" -> 0 if not present!
if (mp.find("banana") != mp.end()) { }  // correct
if (mp.count("banana")) { }             // correct, cleaner
```

### Ordered queries work here too
```cpp
map<int,string> mp = {{10,"a"}, {20,"b"}, {30,"c"}};
auto it = mp.lower_bound(15);   // -> {20,"b"}
it->first;  it->second;         // access via arrow, since *it gives the whole pair
```

---

## 6. `multimap` — Sorted, Duplicate Keys Allowed

Same as `map`, but duplicate keys allowed.

```cpp
#include <map>
multimap<string,int> mm;
mm.insert({"apple", 5});
mm.insert({"apple", 10});   // duplicate key OK
mm.insert({"banana", 2});
```

**Restriction:** No `mp["key"]` operator (ambiguous with duplicate keys) — must use `insert({key, value})`.

**Gotcha:** `mm.erase("apple")` removes **all** pairs with that key.
```cpp
auto it = mm.find("apple");
if (it != mm.end()) mm.erase(it);   // remove just one
```

`mm.count("apple")` = number of values for that key (actually meaningful here).

### Get all values for a key
```cpp
auto range = mm.equal_range("apple");
for (auto it = range.first; it != range.second; it++) cout << it->second << " ";
```

---

## 7. `unordered_map` — Hash-Based Key → Value

Same as `map` but hash-based: **no order**, **O(1) average**. Direct equivalent of Python's `dict`.

```cpp
#include <unordered_map>
unordered_map<string,int> ump;
ump["apple"] = 5; ump["banana"] = 2; ump["cherry"] = 8;
// iteration order not guaranteed
```

Same `[]`, `.count()`, `.find()`, `.erase()`, and same "auto-insert on `[]` access" gotcha as `map`.

### Decision table (map family)
| Need | Use |
|---|---|
| Fast key-value access, no order needed | `unordered_map` — avg O(1), most common default |
| Sorted by key / ordered queries | `map` — O(log n) |
| Duplicate keys + sorted | `multimap` |
| Duplicate keys + no order, fast | `unordered_multimap` |

---

## 8. `stack` — LIFO

Last In, First Out — like a stack of plates.

```cpp
#include <stack>
stack<int> st;
st.push(10); st.push(20); st.push(30);
st.top();   // 30
st.pop();    // removes 30 — NO return value
st.top();   // 20
```

**Gotcha (vs Python):** Python's `list.pop()` returns the value. C++'s `stack.pop()` does **not**. Grab the value with `.top()` before popping:
```cpp
int val = st.top();
st.pop();
```

### Key functions
```cpp
st.push(x);  st.pop();  st.top();  st.empty();  st.size();
```
No random/middle access — by design.

**Use cases:** balanced parentheses, undo functionality, iterative DFS, expression evaluation.

---

## 9. `queue` — FIFO

First In, First Out — like a line at a store.

```cpp
#include <queue>
queue<int> q;
q.push(10); q.push(20); q.push(30);
q.front();  // 10
q.pop();     // removes 10 — no return value
q.front();  // 20
```

### Key functions
```cpp
q.push(x);  q.pop();  q.front();  q.back();  q.empty();  q.size();
```

**Use cases:** BFS, task scheduling, "process in arrival order."

---

## 10. `deque` — Double-Ended Queue

Push/pop from **both ends** in O(1). Like a vector that's also fast at the front (plain `vector` is O(n) at the front).

```cpp
#include <deque>
deque<int> dq;
dq.push_back(10); dq.push_front(5); dq.push_back(20);
for (int x : dq) cout << x << " ";   // 5 10 20
dq.pop_front();   // no return value
dq.pop_back();     // no return value
```

Also supports `dq[i]` random access, `.front()`, `.back()`.

**Use cases:** sliding window problems (sliding window max/min is the classic use case).

---

## 11. `priority_queue` — Heap

Not FIFO or LIFO — always gives the **maximum** element first by default. Heap under the hood.

```cpp
#include <queue>
priority_queue<int> pq;   // max-heap by default
pq.push(10); pq.push(30); pq.push(20);
pq.top();   // 30 (largest, not insertion order)
pq.pop();    // no return value
pq.top();   // 20
```

### Key functions
```cpp
pq.push(x);  pq.pop();  pq.top();  pq.empty();  pq.size();
```

### Min-heap variant
```cpp
priority_queue<int, vector<int>, greater<int>> minPq;
minPq.push(10); minPq.push(30); minPq.push(20);
minPq.top();  // 10 (smallest first)
```
Treat `priority_queue<int, vector<int>, greater<int>>` as a fixed "magic incantation" for min-heap: `vector<int>` = internal storage (default anyway), `greater<int>` = flips ordering to smallest-first.

**Use cases:** Dijkstra's algorithm, "K largest/smallest" problems, merging K sorted lists, heap scheduling.

### Adapter summary table
| Container | Order | Access |
|---|---|---|
| `stack` | LIFO | only top |
| `queue` | FIFO | only front/back |
| `deque` | none (double-ended) | front, back, AND random `dq[i]` |
| `priority_queue` | largest (or smallest) on top | only top |

---

## 12. `list` — Doubly Linked List

**Not** the same as Python's `list`! C++ `list` = doubly linked list. Python `list` = C++ `vector`.

| Name | Actually is |
|---|---|
| Python `list` | dynamic array → C++ `vector` |
| C++ `list` | doubly linked list → closest Python analog: `collections.deque` |

### Trade-off vs vector
| Operation | `vector` | `list` |
|---|---|---|
| Random access `[i]` | O(1) | O(n) — not supported at all |
| Insert/delete in middle | O(n) (shifting) | O(1) (with iterator to spot) |

### Basic usage
```cpp
#include <list>
list<int> l;
l.push_back(10); l.push_front(5); l.push_back(20);   // push_front is O(1)!
for (int x : l) cout << x << " ";   // 5 10 20
l.pop_back();  l.pop_front();
```

### Key functions
```cpp
l.push_back(x);  l.push_front(x);
l.pop_back();  l.pop_front();
l.front();  l.back();
l.size();  l.empty();
l.insert(it, x);  // insert before iterator it — O(1) here
l.erase(it);        // erase at iterator it — O(1) here
l.sort();            // list's OWN sort — can't use generic std::sort (needs random access)
l.reverse();
```

No `l[i]` — if you need indexed access, use `vector` instead.

**Practical note:** Rarely used in competitive programming compared to `vector`. Shows up more in systems/interview contexts (e.g. LRU cache) where O(1) middle insert/delete genuinely matters.

---

## Quick Reference — Complexity Summary

| Container | Insert | Delete | Search | Sorted? | Duplicates? |
|---|---|---|---|---|---|
| `vector` | O(1) amortized (end), O(n) (middle) | O(n) | O(n) | no | yes |
| `list` | O(1) (with iterator) | O(1) (with iterator) | O(n) | no | yes |
| `set` | O(log n) | O(log n) | O(log n) | yes | no |
| `multiset` | O(log n) | O(log n) | O(log n) | yes | yes |
| `unordered_set` | O(1) avg | O(1) avg | O(1) avg | no | no |
| `map` | O(log n) | O(log n) | O(log n) | yes (by key) | no (keys) |
| `multimap` | O(log n) | O(log n) | O(log n) | yes (by key) | yes (keys) |
| `unordered_map` | O(1) avg | O(1) avg | O(1) avg | no | no (keys) |
| `stack` | O(1) | O(1) | — | — | yes |
| `queue` | O(1) | O(1) | — | — | yes |
| `deque` | O(1) both ends | O(1) both ends | O(n) | no | yes |
| `priority_queue` | O(log n) | O(log n) | — (top only) | heap order | yes |

---

## Still to cover (next session)
- `next_permutation()`
- `__builtin_popcount()`
- `sort()`
- `min_element()` / `max_element()`