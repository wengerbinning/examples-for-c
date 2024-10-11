
import subprocess
import sys
import os
import time

class ProjectBuilder:
	def __init__(self, proj, commands, verbose=False):
		self.project = proj
		self.commands = commands
		self.verbose = verbose

	def run(self):
		self._old_cwd = os.getcwd()
		os.chdir(self.project.get("path"))

		idx=0
		for cmd in self.commands:
			idx += 1
			proc = subprocess.Popen(cmd, shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			#
			if self.verbose:
				for line in proc.stdout:
					 print("#:", line.rstrip().decode('utf-8'))
			for line in proc.stderr:
					 print("#:", line.rstrip().decode('utf-8'))
			# outs, errs = process.communicate()

			if 0 == proc.returncode:
				print("Command: {} Error".format(cmd))
				return -1
			#
		os.chdir(self._old_cwd)
