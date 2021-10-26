import os
import sys

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print ("usage: create_csv <base_path>")


    BASE_PATH="yalefaces"
    SEPARATOR=";"

    label = 0
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname)
            for filename in os.listdir(subject_path):
                abs_path = "%s/%s" % (subject_path, filename)
                print ("%s%s%d" % (abs_path, SEPARATOR, label))
            label = label + 1
