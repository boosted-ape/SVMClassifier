import os.path
import sys



#for filename in os.listdir("/Users/bj/LBPH/bj_face/src/face_detection/cropped_faces"):
#   try:
#       subject_no = int(filename[1:3]) 
#       os.rename(filename, "s{count}/{file_name}.jpg".format(count = str(subject_no), file_name = filename))
#   except Exception as e:
#       print(e)


if __name__ == "__main__":

    BASE_PATH="/Users/bj/LBPH/bj_face/src/face_detection/cropped_faces"
    SEPARATOR=";"

    f = open(BASE_PATH + "/data.csv", "a")
    label = 0
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname)
            for filename in os.listdir(subject_path):
                abs_path = "%s/%s" % (subject_path, filename)
                f.write("%s%s%d\n" % (abs_path, SEPARATOR, label))
            label = label + 1

    f.close()
    

