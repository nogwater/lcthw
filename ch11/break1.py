import subprocess
# run ex10 with lots of args

arg_count = 1024 * 32 # 1024 * 16 works
args = ''
for i in range(arg_count):
	args += str(i + 1) + ' '

# print args
subprocess.call(['./ex10 ' + args], shell=True)