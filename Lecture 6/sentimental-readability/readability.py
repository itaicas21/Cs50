def main():
    text = input("Input Text\n")
    word_count=1
    sentence_count=0
    letter_count=0
    for i in range(len(text)):
        if text[i].isalpha():
            letter_count+=1
        elif text[i]==' ':
            word_count+=1
        elif text[i]=='.' or text[i]=='?' or text[i]=='!':
            sentence_count+=1
    index=round(0.0588*((letter_count/word_count)*100)-0.296*((sentence_count/word_count)*100)-15.8)
    if (index <1):
        print("Before Grade 1")
    elif (index>16):
        print("Grade 16+")
    else:
        print("Grade "+str(index))

if __name__ == '__main__':
    main()