import os
import xml.etree.ElementTree as xmltree

class ProjectManager:
	counter = 0
	projects = dict()
	ignore_projects = list()

	def __init__(self, path):
		#
		home = ".project"
		if not os.path.exists(home):
			os.mkdir(home)
		#
		ignore = "{0}/ignore-project".format(home)
		if os.path.exists(ignore):
			with open(ignore, 'r', encoding='utf-8') as file:
				for line in file:
					if line.strip() == '':
						continue
					self.ignore_projects.append(line.rstrip('\n'))
		#
		if os.path.exists(path):
			tree = xmltree.parse(path)
			root = tree.getroot()
			for node1 in root.findall("path"):
				home = node1.get('name')
				for node2 in node1.findall('module'):
					proj = {}
					mod = node2.get('name')
					pri = int(node2.get('priority'))
					proj["id"] = self.counter
					proj["name"] = mod
					proj["path"] = "{0}/{1}".format(home, mod)
					self.counter += 1
					list1 = self.projects.get(pri, [])
					list1.append(proj)
					self.projects.update({pri:list1})

	def __next__(self):
		for pri in self.projects.keys():
			for mod in self.projects.get(pri):
				yield (pri, mod)

	def __iter__(self):
		return self.__next__()






		os.chdir(self._old_cwd)
