#include <cstddef>
#include <map>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct ListNode {
    int idx;
    shared_ptr<ListNode> next;
    shared_ptr<ListNode> prev;
    ListNode(int id) : idx(id), next(NULL), prev(NULL) {}
};

struct node_pair{
    int first;
    int last;
    node_pair(int a, int b) : first(a), last(b) {}
};

int find_min_cost(map<int, shared_ptr<ListNode>> &city_map, int first, int last, int min_cost) {

   vector<node_pair> pairs;
    int mid1 = first + 1;
    int mid2 = mid1;
    while (mid2 != last) {
        if (city_map.find(mid2) != city_map.end()) {
            auto node = city_map[mid2];
            while (node) {
                mid2 = node->idx;
                node = node->next;
            }
        }
        cout << "node pair: " << mid1 << ", " << mid2 << endl;
        auto cost = (mid1 - first) * (mid1 - first) + (last - mid2) * (last - mid2);
        if (cost < min_cost) {
            min_cost = cost;
            cout << "min_cost:" << min_cost <<  ", city: " << mid1 << ", " << mid2 << endl;
        }

        mid1 = mid2 + 1;
        mid2 = mid1;

    }

    return min_cost;

}

int find_min(map<int, shared_ptr<ListNode>> &city_map, int N) {
    int first = 1;
    int last = N;
    if (city_map.find(first) != city_map.end()) {
        auto node = city_map[first];
        while (node) {
            first = node->idx;
            node = node->next;
        }
    }
    if (city_map.find(last) != city_map.end()) {
        auto node = city_map[last];
        while (node) {
            last = node->idx;
            node = node->prev;
        }
    }

    int min_cost = (last - first) * (last - first);
    return find_min_cost(city_map, first, last, min_cost);

}

void find() {
    int N, M;
    cin >> N;
    cin >> M;
    map<int, shared_ptr<ListNode>> city_map;
    for (int j = 0; j < M; j++) {
        int a, b;
        cin >> a;
        cin >> b;
        shared_ptr<ListNode> first = nullptr;
        shared_ptr<ListNode> second = nullptr;
        if (city_map.find(a) == city_map.end()) {
            first = make_shared<ListNode>(a);
            city_map[a] = first;
        } else {
            first = city_map[a];
        }
        if (city_map.find(b) == city_map.end()) {
            second = make_shared<ListNode>(b);
            city_map[b] = second;
        } else {
            second = city_map[b];
        }
        first->next = second;
        second->prev = first;
    }
    int ret = find_min(city_map, N);
    for (auto &entry : city_map) {
        entry.second->next = nullptr;
        entry.second->prev = nullptr;
    }
    cout << ret << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        find();
    }

    return 0;
}