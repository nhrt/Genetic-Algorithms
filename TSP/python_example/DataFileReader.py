from typing import List
from Position import Position


def read_city_positions(file_path: str,  skip_lines: int) -> List[Position]:
	city_positions: List[Position] = []
	with open(file_path, 'r') as reader:
		lines_list: List[str] = reader.readlines()
		for idx in range(skip_lines, len(lines_list)):
			coords: List[str] = lines_list[idx].split()
			city_positions.append(Position(int(coords[0]), int(coords[1])))
	return city_positions


def read_best_roundtrip(file_path: str,  skip_lines: int) -> List[int]:
	city_idxs: List[int] = []
	with open(file_path, 'r') as reader:
		lines_list: List[str] = reader.readlines()
		for idx in range(skip_lines, len(lines_list)):
			city_idxs.append(int(lines_list[idx].split()[0])-1)
	return city_idxs
