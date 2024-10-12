
import subprocess
import sys
import os
import time

class Worker:
	idx = 0
	def __init__(self, cwd):
		self.cwd = cwd

	def __enter__(self):
		self.old_cwd = os.getcwd()
		os.chdir(self.cwd)
		return self

	def __exit__(self, exc_type, exc_val, exc_tb):
		os.chdir(self.old_cwd)
		return True

	def do(self, cmd):
		self.idx += 1
		print("\033[32m #{1} {2}\033[0m in {0}".format(os.getcwd(), self.idx, ' '.join(cmd)))
		proc = subprocess.Popen(cmd)
		while proc.poll() is None:
			# 	line = proc.stdout.readline()
			# 	if line.strip() != '':
			# 		print("\033[32m>\033[0m", line.rstrip().decode('utf-8'))
			# 	line = proc.stderr.readline()
			# 	if line.strip() != '':
			# 		print("\033[33m>\033[0m", line.rstrip().decode('utf-8'))
			# 获取stdout和stderr输出
			out, err = proc.communicate()

			# 打印stdout和stderr输出
			# sys.stdout.write("OUT#" + out.decode('utf-8'))
			# sys.stderr.write("ERR#" + err.decode('utf-8'))

			# if 0 != proc.returncode:
			# 	print("Command: {0} Error {1}".format(cmd, proc.returncode))
			# 	return -1

			#

class ProjectBuilder:
	def __init__(self, proj, commands, verbose=False):
		self.project = proj
		self.commands = commands
		self.verbose = verbose

	def run(self):
		with Worker(self.project.get("path")) as worker:
			for cmd in self.commands:
				worker.do(cmd)
