#include <iostream>
#include <list>
using std::list;
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
using Keys = std::vector<std::string>;
int GetRandom(int v) {
	return (v * 27073 + 17713) % 32749;
}
std::string GetKey(char op, int v) {
	return std::string({ op }) + std::to_string(v);
}
class Block {
public:
	std::pair<int, int> pos[4];
	char shape;
	int order;
	Block(char shap, int orde) {
		shape = shap;
		pos[0] = { 0, 0 };
		switch (shape) {
		case 'i':
			pos[1] = { 0, -1 };
			pos[2] = { 0, -2 };
			pos[3] = { 0, 1 };
			order = orde & 1;
			break;
		case 'l':
			pos[1] = { 0, -1 };
			pos[2] = { 0, -2 };
			pos[3] = { 1, 0 };
			order = orde & 3;
			break;
		case 'j':
			pos[1] = { 0, -1 };
			pos[2] = { 0, -2 };
			pos[3] = { -1, 0 };
			order = orde & 3;
			break;
		case 't':
			pos[1] = { -1, 0 };
			pos[2] = { 1, 0 };
			pos[3] = { 0, 1 };
			order = orde & 3;
			break;
		case 'o':
			pos[1] = { 0, -1 };
			pos[2] = { 1, -1 };
			pos[3] = { 1, 0 };
			order = 0;
			break;
		case 's':
			pos[1] = { 0, -1 };
			pos[2] = { 1, -1 };
			pos[3] = { -1, 0 };
			order = orde & 1;
			if (order == 1) order = 3;
			break;
		case 'z':
			pos[1] = { 0, -1 };
			pos[2] = { 1, 0 };
			pos[3] = { -1, -1 };
			order = orde & 1;
			if (order == 1) order = 3;
			break;
		}
		for (int rotation = 0; rotation < order; rotation++)
			for (int i = 1; i < 4; i++) {
				auto p = pos[i];
				pos[i] = std::pair<int, int>{ -p.second, p.first };
			}
	}
	Block() {}

	bool OutOfLR() {
		bool res = false;
		for (auto p : pos) {
			if (p.first < -4 || p.first > 5) return true;
		}
		return res;
	}

	void Right(int right) {
		for (auto& p : pos) {
			p.first += right;
		}
	}
	void Down(int down) {
		for (auto& p : pos) {
			p.second += down;
		}
	}
	void print(std::ostream& out) const {
		char map[5][10];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				map[i][j] = '.';
			}
		}
		for (auto p : pos) {
			map[p.second + 2][p.first + 4] = '#';
		}
		for (int i = 0; i < 5; i++) {
			if (i >= 2) out << i - 2;
			else out << ' ';
			for (int j = 0; j < 10; j++) {
				out << map[i][j];
			}
			out << std::endl;
		}
	}



	std::vector<std::pair<Keys, Block>> GetAll() {
		std::vector<std::pair<Keys, Block>> res;
		Block block;
		switch (shape)
		{
		case 'o':
			block = Block(shape, 0);
			block.Right(-4);
			for (int i = -4; i <= 4; i++) {
				if (i < 0) {
					res.push_back({ Keys({GetKey('L', -i)}), block });
				}
				else if (i == 0) {
					res.push_back({ Keys(),block });
				}
				else {
					res.push_back({ Keys({GetKey('R', i)}), block });
				}
				block.Right(1);
			}
			break;
		case 'i':
			if (order == 0) {
				block = Block(shape, 0);
				block.Right(-4);
				for (int i = -4; i <= 5; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys(),block });
					}
					else {
						res.push_back({ Keys({GetKey('R', i)}), block });
					}
					block.Right(1);
				}
				block = Block(shape, 1);
				block.Right(-3);
				for (int i = -3; i <= 3; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('C', 1), GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys({GetKey('C', 1)}), block });
					}
					else {
						res.push_back({ Keys({GetKey('C', 1), GetKey('R', i)}), block });
					}
					block.Right(1);
				}
			}
			else {
				block = Block(shape, 1);
				block.Right(-3);
				for (int i = -3; i <= 3; i++) {

					if (i < 0) {
						res.push_back({ Keys({GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys(), block });
					}
					else {
						res.push_back({ Keys({GetKey('R', i)}), block });
					}
					block.Right(1);
				}
				block = Block(shape, 0);
				block.Right(-4);
				for (int i = -4; i <= 5; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('C', 1), GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys({GetKey('C', 1)}),block });
					}
					else {
						res.push_back({ Keys({GetKey('C', 1), GetKey('R', i)}), block });
					}
					block.Right(1);
				}
			}
			break;
		case 's':
		case 'z':
			if (order == 0) {
				block = Block(shape, 0);
				block.Right(-3);
				for (int i = -3; i <= 4; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys(),block });
					}
					else {
						res.push_back({ Keys({GetKey('R', i)}), block });
					}
					block.Right(1);
				}
				block = Block(shape, 1);
				block.Right(-3);
				for (int i = -3; i <= 5; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('C', 1), GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys({GetKey('C', 1)}), block });
					}
					else {
						res.push_back({ Keys({GetKey('C', 1), GetKey('R', i)}), block });
					}
					block.Right(1);
				}
			}
			else {
				block = Block(shape, 1);
				block.Right(-3);
				for (int i = -3; i <= 5; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys(),block });
					}
					else {
						res.push_back({ Keys({GetKey('R', i)}), block });
					}
					block.Right(1);
				}
				block = Block(shape, 0);
				block.Right(-3);
				for (int i = -3; i <= 4; i++) {
					if (i < 0) {
						res.push_back({ Keys({GetKey('C', 1), GetKey('L', -i)}), block });
					}
					else if (i == 0) {
						res.push_back({ Keys({GetKey('C', 1)}), block });
					}
					else {
						res.push_back({ Keys({GetKey('C', 1), GetKey('R', i)}), block });
					}
					block.Right(1);
				}
			}
			break;
		case 't':
		case 'j':
		case 'l':
			for (int c = 0; c <= 3; c++) {
				block = Block(shape, order + c);
				block.Right(-6);
				for (int i = -6; i <= 6; i++) {
					Keys keys;
					if (c != 0) keys.push_back(GetKey('C', c));
					if (!block.OutOfLR()) {
						if (i < 0)
							keys.push_back(GetKey('L', -i));
						else if (i > 0)
							keys.push_back(GetKey('R', i));
						res.push_back({ keys, block });
					}
					block.Right(1);
				}
			}
			break;
		}
		return res;
	}
};

class Line {
public:
	bool block[10] = { 0 };
	int sum = 0;
};

int holepunish = 0;
int flatpunish = 0;

float heightpoint[21] = {
	0, 
	// 10, 21, 27, 17, 6, 
	//-6, -19, -28, -42, -51
	-100, -100, -100, -100, -100, -100, -100,
	-100, -100, -100,
	-58, -66, -71, -76, -86, 
	-99, -104, -112, -123, -129 
};
void SetRand() {
	int bound = rand() % 8 + 1;
	for (int i = 1; i < bound; i++) {
		heightpoint[i] = heightpoint[i - 1] + rand() % 10 + 5;
	}
	for (int i = bound; i < 21; i++) {
		heightpoint[i] = heightpoint[i - 1] - rand() % 10 - 5;
	}
	/*holepunish = rand() % 20 + 5;
	flatpunish = rand() % 15 + 3;*/
}

float PartNice(int h, int s, int len) {
	if (h == 0) return heightpoint[0];
	float p = s / ((float)len * h);
	int lack = len * h - s;
	return heightpoint[h] - h * 2 * lack;
}

class Blocks {
private:

public:
	list<Line> lines;
	int sum;
	int point;
	bool alive;
	int height[10];
	Blocks() :height{ 0 } {
		for (int i = 0; i < 20; i++) {
			lines.push_back(Line());
		}
		sum = 0;
		point = 0;
		alive = true;
	}
	Blocks(Blocks* p) {
		lines = p->lines;
		sum = p->sum;
		point = p->point;
		alive = p->alive;
		for (int i = 0; i < 10; i++) {
			height[i] = p->height[i];
		}
	}
	Blocks(int zero) :height{ 0 } {
		alive = false;
		sum = 0;
		point = 0;
		lines = list<Line>();
	}
	void print(std::ostream& out) {
		for (const auto& line : lines) {
			for (int i = 0; i < 10; i++) {
				if (line.block[i]) out << '#';
				else out << '.';
			}
			out << std::endl;
		}
		out << std::endl;
	}
	Blocks add(Block block, int& down) {
		// 向右移了多少格
		int min = 100;
		int max = -100;

		down = 100;
		for (auto p : block.pos) {
			int x = p.first + 4;

			int maxdown = -100;
			maxdown = 19 - height[x] - p.second;

			if (maxdown < down) {
				down = maxdown;
			}
		}
		if (down <= 0) {
			down = -1;
			alive = false;
			return Blocks(0);
		}
		block.Down(down);
		Blocks res(this);
		int curdown = 0;
		int i = 0;
		for (auto& line : res.lines) {
			for (const auto& p : block.pos) {
				if (p.second == curdown) {
					if (res.height[p.first + 4] < 20 - curdown) {
						res.height[p.first + 4] = 20 - curdown;
					}
					line.block[p.first + 4] = true;
					line.sum++;
					res.sum++;
					i++;
				}
			}
			if (i == 4) break;
			curdown++;
		}
		res.Eliminate();
		return res;
	}
	void addin(Block block, int down) {
		block.Down(down);
		int curdown = 0;
		int i = 0;
		for (auto& line : lines) {
			for (const auto& p : block.pos) {
				if (p.second == curdown) {
					if (height[p.first + 4] < 20 - curdown) {
						height[p.first + 4] = 20 - curdown;
					}
					line.block[p.first + 4] = true;
					line.sum++;
					sum++;
					i++;
				}
			}
			if (i == 4) break;
			curdown++;
		}
		Eliminate(true);
	}
	void Eliminate(bool addpoint = false) {
		for (auto it = lines.begin(); it != lines.end(); ) {
			if (it->sum == 10) it = lines.erase(it);
			else it++;
		}
		int eliminate = 20 - lines.size();
		if (addpoint) point = point + eliminate * (eliminate + 1) / 2 * sum;
		sum -= eliminate * 10;

		for (int i = 0; i < eliminate; i++) {
			lines.push_front(Line());
		}
		if (eliminate > 0) {
			int curheight = 1;
			for (auto it = lines.rbegin(); it != lines.rend(); it++) {
				for (int i = 0; i < 10; i++) {
					if (it->block[i]) {
						height[i] = curheight;
					}
				}
				curheight++;
			}
		}
	}
	float Nice() {
		int hl = 0, hr = 0, h = 0;	// 高度
		int sl = 0, sr = 0, s = 0;	// 方块数
		int cur = 1;
		int hole = -sum;
		for (int i = 0; i < 10; i++) {
			hole += height[i];
		}
		int unflat = 0;
		for (int i = 0; i < 9; i++) {
			unflat += std::abs(height[i] - height[i + 1]);
		}
		float res = -holepunish * hole - flatpunish * unflat;
		for (auto it = lines.rbegin(); it != lines.rend(); it++) {
			const auto& line = *it;
			res += it->sum * heightpoint[cur];
			cur++;
		}
		return res;
	}
};

std::map<char, std::vector<std::vector<std::pair<Keys, Block>>>> ops;
std::vector<std::pair<char, int>> table;
#include <ctime>
void Init() {
	std::srand(std::time(0));
	ops['i'] = std::vector<std::vector<std::pair<Keys, Block>>>();
	ops['l'] = std::vector<std::vector<std::pair<Keys, Block>>>();
	ops['j'] = std::vector<std::vector<std::pair<Keys, Block>>>();
	ops['t'] = std::vector<std::vector<std::pair<Keys, Block>>>();
	ops['o'] = std::vector<std::vector<std::pair<Keys, Block>>>();
	ops['s'] = std::vector<std::vector<std::pair<Keys, Block>>>();
	ops['z'] = std::vector<std::vector<std::pair<Keys, Block>>>();

	char c;
	c = 'o';
	for (int i = 0; i < 1; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());
	}
	c = 'i';
	for (int i = 0; i < 2; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());
	}
	c = 's';
	for (int i = 0; i < 2; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());
	}
	c = 'z';
	for (int i = 0; i < 2; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());
	}
	c = 'l';
	for (int i = 0; i < 4; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());
	}
	c = 'j';
	for (int i = 0; i < 4; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());
	}
	c = 't';
	for (int i = 0; i < 4; i++) {
		Block block(c, i);
		ops[c].push_back(block.GetAll());

	}

	int v = 12358;
	int order;
	for (int i = 0; i < 10010; i++) {
		v = GetRandom(v);
		int weightIndex = v % 29;
		char shape = 0;
		if (weightIndex >= 0 && weightIndex <= 1) {
			shape = 'i';
			order = i % 2;
		}
		else if (weightIndex > 1 && weightIndex <= 4) {
			shape = 'l';
			order = i % 4;
		}
		else if (weightIndex > 4 && weightIndex <= 7) {
			shape = 'j';
			order = i % 4;
		}
		else if (weightIndex > 7 && weightIndex <= 11) {
			shape = 't';
			order = i % 4;
		}
		else if (weightIndex > 11 && weightIndex <= 16) {
			shape = 'o';
			order = 0;
		}
		else if (weightIndex > 16 && weightIndex <= 22) {
			shape = 's';
			order = i % 2;
		}
		else if (weightIndex > 22) {
			shape = 'z';
			order = i % 2;
		}
		table.push_back({ shape, order });
	}
}
#include <queue>
using std::priority_queue;
Keys FindBest(Blocks& curmap, int nextid, int deep, float& best) {
	best = -100000;
	int bestid = -10000;
	int bestdown = -10000;
	char shape = table[nextid].first;
	int order = table[nextid].second;
	if (deep == 1) {
		Block nextblock = Block(shape, order);
		int opsnum = ops[shape][order].size();
		for (int i = 0; i < opsnum; i++) {
			const std::pair<Keys, Block>& valid = ops[shape][order][i];
			int down;
			Blocks newmap = curmap.add(valid.second, down);
			float score = -100000;
			if (newmap.alive) {
				score = newmap.Nice();
			}
			else score = -10000000;
			if (score > best) {
				best = score;
				bestid = i;
				bestdown = down;
			}
		}
	}
	else {
		Block nextblock = Block(shape, order);
		int opsnum = ops[shape][order].size();
		priority_queue<int, std::vector<int>, std::less<int>> pq;
		for (int i = 0; i < opsnum; i++) {

			const std::pair<Keys, Block>& valid = ops[shape][order][i];
			int down;
			Blocks newmap = curmap.add(valid.second, down);
			if (newmap.alive) {
				float score = -100000;
				if (pq.size() > 10) {
					int nice = newmap.Nice();
					if (nice >= pq.top()) {
						pq.pop();
						pq.push(nice);
					}
					else continue;
				}
				else {
					pq.push(newmap.Nice());
				}
				FindBest(newmap, nextid + 1, deep - 1, score);
				if (score > best) {
					best = score;
					bestid = i;
					bestdown = down;
				}
			}
		}
	}
	if (bestid == -10000) return Keys();
	Keys res = ops[shape][order][bestid].first;
	res.push_back(GetKey('D', bestdown));
	curmap.addin(ops[shape][order][bestid].second, bestdown);
	return std::move(res);
}

void Build(const std::vector<std::string> &ops, int &i, Blocks &map, std::ostream &out, int blocks) {
	char shape;
	int order;
	int right;
	int l, r, c, d;
	Block block;
	for (std::string op : ops) {
		switch (op[0]) {
		case 'N':
			shape = table[i].first;
			order = table[i].second;
			i++;
			right = 0;
			if (i >= blocks) {
				i--;
				return ;
			}
			else {
				out << op << ',';
			}
			break;
		case 'D':
			 d = std::stoi(op.substr(1));
			block = Block(shape, order);
			block.Right(right);
			map.addin(block, d);
			out << op << ',';
			break;
		case 'L':
			 l = std::stoi(op.substr(1));
			right = -l;
			out << op << ',';
			break;
		case 'R':
			 r = std::stoi(op.substr(1));
			right = r;
			out << op << ',';
			break;
		case 'C':
			 c = std::stoi(op.substr(1));
			order += c;
			out << op << ',';
			break;
		}
	}
}

int main() {
	Init();
	std::ofstream out("out.txt");
	std::ifstream in("in.txt");
	std::string opstr;
	in >> opstr;
	std::vector<std::string> ops;

	std::string temp;
	for (char c : opstr) {
		if (c != ',') temp.push_back(c);
		else {
			ops.push_back(temp);
			temp.clear();
		}
	}
	temp.clear();

	int bestpoint = 130384;
	int useblock = 3870;

	for (int it = 0; it < 3000; it++) {
		/*for (holepunish = 10; holepunish <= 20; holepunish++) {
			for (flatpunish = 3; flatpunish <= 13; flatpunish++) {*/
		holepunish = rand() % 10 + 10;
		flatpunish = rand() % 10 + 3;
		Blocks map;
		std::stringstream sout;
		out << "axios.post(`api/upload`, { record: '";

		int i = 0;
		Build(ops, i, map, sout, useblock - 100);
		map.print(std::cout);
		std::cout << map.point << std::endl;
		float score;
		for (; i < 10000; i++) {
			sout << "N";
			Keys keys = FindBest(map, i, (4 - i % 3), score);
			// Keys keys = FindBest(map, i, 3, score);
			if (score <= -100000) break;
			for (auto key : keys) {
				sout << "," << key;
			}
			std::cout << i << ':' << map.point << '\n';
			if (i != 10000) sout << ',';
		}

		std::string newops;
		sout >> newops;
		sout.clear();

		
		if (((double)map.point / (i + 1) > ((double)bestpoint / (useblock + 1)))) {
			out << newops << "', score: ";
			out << map.point;
			out << " }).then(({data}) => { console.log('提交结果', data); if (data.info) { console.log(data.info) } }); ";
			out << std::endl << "score = " << map.point << std::endl << std::endl;;
			out.flush();

			bestpoint = map.point;
			useblock = i;
			ops.clear();
			temp.clear();
			opstr = std::move(newops);
			for (char c : opstr) {
				if (c != ',') temp.push_back(c);
				else {
					ops.push_back(temp);
					temp.clear();
				}
			}

		}
		if (i == 10000) break;
	}

	out.close();
}