#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <functional>

namespace ggcc {
	
	// 多叉树
	template <class T>
	class tree_node {
	private:
		T node_value;
		tree_node<T>* node_father = nullptr;
		std::vector<tree_node<T>*> child_node;
	public:
		~tree_node() {
			if (node_father != nullptr) return;
			for (auto *i : child_node) delete i;
		}
		void set(const T& value_) {
			node_value = value_;
		}
		tree_node<T>& child(int id) {
			while (id >= child_node.size()) {
				tree_node<T>* node = new tree_node<T>;
				node->node_father = this;
				child_node.push_back(node);
			}
			return *child_node[id];
		}
		tree_node<T>& father() {
			return *node_father;
		}
		T& value() {
			return node_value;
		}
		std::vector<tree_node<T>*>& children() {
			return child_node;
		}
		int size() {
			return child_node.size();
		}
	};
	
	// 无限地图
	template <class T, unsigned block_size>
	class boundless_map_block {
	private:
		T block[block_size][block_size];
	public:
		boundless_map_block() {}
		unsigned size() {
			return block_size;
		}
		T& value(int x, int y) {
			return block[x][y];
		}
	};
	template <class T, unsigned block_size = 16>
	class boundless_map {
	private:
		std::unordered_map <long long, boundless_map_block<T, block_size> > block;
		boundless_map_block <T, block_size> empty_block;
		std::function <bool(int, int, boundless_map_block<T, block_size>&)> load_fun = [](int x, int y, boundless_map_block<T, block_size>& block) ->bool {
			return true;
		};
	public:
		long long hash(int x, int y) {
			return x * 1000000007ll + y * 1000000009ll;
		}
		boundless_map() {}
		T& value(int x, int y) {
			int bx = std::floor(1.0 * x / block_size) * block_size;
			int by = std::floor(1.0 * y / block_size) * block_size;
			if (block.count(hash(bx, by)) == 0) {
				if (!load_fun) return empty_block.value(x - bx, y - by);
				boundless_map_block <T, block_size> temp;
				bool op = load_fun(bx, by, temp);
				if (op) {
					block[hash(bx, by)] = temp;
					return block[hash(bx, by)].value(x - bx, y - by);
				}
				return empty_block.value(x - bx, y - by);
			}
			return block[hash(bx, by)].value(x - bx, y - by);
		}
		void set_loadfun(std::function <bool(int, int, boundless_map_block<T, block_size>&)> fun) {
			load_fun = fun;
		}
		bool contain(int x, int y) {
			int bx = std::floor(1.0 * x / block_size) * block_size;
			int by = std::floor(1.0 * y / block_size) * block_size;
			return block.count(hash(bx, by));
		}
	};

}
