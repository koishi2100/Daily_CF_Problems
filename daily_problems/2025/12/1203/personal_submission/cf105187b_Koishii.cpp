#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Fenwick {
	int n;
	std::vector<T> t;

	explicit Fenwick(int _n = 0) : n(_n) {
		t.assign(_n + 1, T{});
	}

	void add(int i, const T& x) {
		i++;
		while (i <= n) {
			t[i] += x;
			i += i & -i;
		}
	}

	T sum(int i) {
		i++;
		T ans = 0;
		while (i) {
			ans += t[i];
			i -= i & -i;
		}
		return ans;
	}


	int kth(T k) {
		int x = 0;
		T ans = 0;
		for (int i = std::log2(n); i >= 0; i--) {
			int nx = x + (1 << i);
			if (nx <= n && ans + t[nx] < k) {
				x = nx;
				ans += t[x];
			}
		}
		return x + 1;
	}

	T sum(int l, int r) { return sum(r) - sum(l - 1); }
	T query(int i) { return sum(i); }
	T query(int l, int r) { return sum(l, r); }
};

void soviet() {
	int n; std::cin >> n;
	std::vector<int> nums(2 * n);
	for (int &x : nums) std::cin >> x;

	std::vector<std::pair<int, int>> competitions(n);
	for (auto &[x, y] : competitions) std::cin >> x >> y;

	Fenwick<int> fen(500010);

	for (auto &[u, v] : competitions) {
		int x = nums[u], y = nums[v];
		if (x > y) std::swap(x, y);
		fen.add(x, 1);
		fen.add(std::min(std::max(x + 1, y + 1), std::max(x + 3, y)), 1);
	}

	std::vector<int> ans(2 * n);

	for (auto &[u, v]: competitions) {
		int x = nums[u], y = nums[v];
		if (x > y) std::swap(x, y);

		fen.add(x, -1);
		fen.add(std::min(std::max(x + 1, y + 1), std::max(x + 3, y)), -1);

		ans[u] = 2 * n - fen.sum(0, nums[u] + 3);
		ans[v] = 2 * n - fen.sum(0, nums[v] + 3);

		if (nums[u] + 3 >= nums[v]) ans[u]--;
		if (nums[v] + 3 >= nums[u]) ans[v]--;

		fen.add(x, 1);
		fen.add(std::min(std::max(x + 1, y + 1), std::max(x + 3, y)), 1);
	}
	for (auto &x : ans) {
		std::cout << x << ' ';
	}
}

int main() {
	int M_T = 1; std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
//	std::cin >> M_T;
	while (M_T--) { soviet(); }
	return 0;
}
