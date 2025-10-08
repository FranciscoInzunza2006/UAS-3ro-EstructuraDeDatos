
def main():
    arr = [1,3,2,5,6,9,0,8,7,4]

    value_to_insert = 404
    index_to_insert = 3

    arr.insert(index_to_insert, value_to_insert)
    arr.pop()
    
    for x in arr:
        print(x, end=" ")

if __name__ == "__main__":
    main()