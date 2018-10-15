import pandas as pd
m1 = pd.read_csv('/Users/leonardodalcin/Downloads/carol-fi-master/matrix1.txt')
m2 = pd.read_csv('/Users/leonardodalcin/Downloads/carol-fi-master/matrix2.txt')

def compare_matrix(m1,m2,compare_function):
	for column in m1:
		for row in m1:
			m1_number = m1[row][int(column)]
			m2_number = m2[row][int(column)]
			if not compare_function(m1_number,m2_number):
				return False

	return True


def compare_threshold(n1,n2):
	is_different = abs(n1-n2) < 0.3
	return is_different

print(compare_matrix(m1,m2,compare_threshold))