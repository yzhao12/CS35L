import sys, locale, string
from optparse import OptionParser


def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2 
Select or reject lines common to two files"""

    locale.setlocale(locale.LC_ALL, '')
    
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1", "--one", action="store_true", dest="one", default=False)
    parser.add_option("-2", "--two", action="store_true", dest="two", default=False)
    parser.add_option("-3", "--three", action="store_true", dest="three", default=False)
    parser.add_option("-u", "--unsorted", action="store_true", dest="unsorted", default=False)
    options, args = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        parser.error("wrong number of operands")

    file1 = args[0]
    file2 = args[1]

    if file1 == "-":
        lines1 = sys.stdin.readlines()
        f2 = open(file2, 'r')
        lines2 = f2.readlines()
        f2.close()
    elif file2 == "-":
        lines2 = sys.stdin.readlines()
        f1 = open(file1, 'r')
        lines1 = f1.readlines()
        f1.close()
    else:
        f1 = open(file1, 'r')
        lines1 = f1.readlines()
        f1.close()
        f2 = open(file2, 'r')
        lines2 = f2.readlines()
        f2.close()
        
    if options.unsorted == False:
        inboth = []
        preallwords = lines1 + lines2
        preallwords = list(set(preallwords))
        lines22 = []
        for a in lines2:
            lines22.append(a)
        for a in preallwords:
            if a in lines1 and a in lines2:
                inboth.append(a)

        for b in inboth:
            lines22.remove(b)

        allwords = lines1 + lines22
        allwords.sort()
        for i in range(len(allwords)):
            if allwords[i] in lines1 and allwords[i] not in lines2:
                if options.one == False:
                    sys.stdout.write(allwords[i])
            if allwords[i] in lines2 and allwords[i] not in lines1:
                if options.two == False:
                    sys.stdout.write('\t' + allwords[i])
            if allwords[i] in lines1 and allwords[i] in lines2:
                if options.three == False:
                    sys.stdout.write('\t' + '\t' + allwords[i])
    elif options.unsorted == True:
        for line1 in lines1:
            if line1 not in lines2:
                if options.one == False:
                    sys.stdout.write(line1)
            elif line1 in lines2:
                lines2.remove(line1)
                if options.three == False:
                    sys.stdout.write('\t' + '\t' + line1)

        for line2 in lines2:
            if options.two == False:
                sys.stdout.write('\t' + line2)


if __name__ == "__main__":
    main()
