
def main():
    arr = [1,3,2,5,6,9,0,8,7,4]

    target = -1
    found = -1
    for i in range(len(arr)):
        if (arr[i] == target):
            found = 1
            break
    
    print(arr)
    if (found != -1):
        print(f"{target} is in the index {found}")
    else: 
        print(f"{target} isn't on the array")

if __name__ == "__main__":
    main()