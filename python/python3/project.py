#!/usr/bin/env python

import xml.etree.ElementTree as xmltree

class ProjectManager:
	counter = 0
	projects = dict()
	def __init__(self, path):
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
				yield (pri,mod)

	def __iter__(self):
		return self.__next__()

class ProjectBuilder:
	def __init__(self, proj, commands):
		self.project = proj
		self.commands = commands

	def run(self):
		print("Start build ", self.project.get("name"))
		for cmd in self.commands:
			print(cmd)

mainfest = "build_path/default.xml"

projects = ProjectManager(mainfest)

commands = [
	"ls",
	"who"
]

for prio, proj in projects:
	build = ProjectBuilder(proj, commands)
	build.run()