from typing import List


class Position:
	def __init__(self, x: int, y: int):
		self.x = x
		self.y = y

	def __str__(self):
		return "({} | {})".format(self.x, self.y)

	@staticmethod
	def convert_idxs_to_positions(roundtrip: List[int], city_positions: List['Position']) -> List['Position']:
		return [city_positions[r] for r in roundtrip]
