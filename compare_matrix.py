import pandas as pd
m1 = pd.read_csv('matrix1.txt')
m2 = pd.read_csv('matrix2.txt')

def compare_threshold(n1,n2, err):
        acceptable = abs(n1-n2) <= err
        return acceptable


def compare_matrix(m1,m2,err):
        for column in m1:
                for row in m1:
                        m1_number = m1[row][int(column)]
                        m2_number = m2[row][int(column)]
                        if not compare_threshold(m1_number,m2_number,err):
                                return False
	return True


def main():

        print(compare_matrix(m1,m2,3e-1))
        print(compare_matrix(m1,m2,3e-2))
        print(compare_matrix(m1,m1,0.0))
        print(compare_matrix(m2,m2,0.0))

if __name__ == '__main__':
        main()
