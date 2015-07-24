# Load mnist.pickle.gz, save it as train/test images in dir train/test respectively, and output train_label.txt, test_label.txt

import sys, os
import cPickle, gzip
import numpy as np
import scipy.misc


def row2img(row):
    """Reshape row to image"""
    return row.reshape( (28, 28) )


def to_gray_scale_imgs(rows):
    """Reshape each rows into gray scale images"""
    imgs = []
    for row in rows:
        img = row.reshape( (28, 28) )
        imgs.append(img)
    return imgs


def save_images(output_dir, images):
    """Save images into output directory"""
    old_path = os.getcwd()
    os.chdir(output_dir)
    img_names = []
    for i,image in enumerate(images):
        img_name = '{0}.jpg'.format(i)
        img_names.append(img_name)
        scipy.misc.imsave(img_name, image)
    os.chdir(old_path)
    return img_names


def save_labels(output_name, img_names, label_arr):
    """Save name-label pairs as space-separated format file"""
    f = open(output_name, 'w')
    for i,label in enumerate(label_arr):
        f.write( img_names[i] + ' ' + label.astype(str) + '\n' )
    f.close()


if __name__ == '__main__':

    # Print help information
    if len(sys.argv[1:]) != 1:
        print """
        Load mnist.pickle.gz, save it as train/test images in dir train/test respectively, and output train_label.txt, test_label.txt
        Usage: python save_mnist_as_image.py [mnist pickle gzip file]

        # mnist pickle gzip file: mnist.pickle.gz from http://deeplearning.net/tutorial/gettingstarted.html
        """
        exit()

    # Load train, val, test
    f = gzip.open('mnist.pkl.gz', 'rb')
    train_set, valid_set, test_set = cPickle.load(f)
    f.close()

    # Set data and label of train, val, test respectively
    train, train_label = train_set
    val, val_label = valid_set
    test, test_label = test_set

    # Aggregate train and val as new_train
    new_train = np.concatenate( (train, val), axis=0 )
    new_train_label = np.concatenate( (train_label, val_label), axis=0 )

    # Reshape each rows of new_train, test into gray-scale images
    new_train = to_gray_scale_imgs(new_train)
    test = to_gray_scale_imgs(test)

    # Make train/test directory under current working directory
    if not os.path.exists('train'):
        os.mkdir('train')
    else:
        raise OSError('directory or file train already exist')

    if not os.path.exists('test'):
        os.mkdir('test')
    else:
        raise OSError('directory or file test already exist')

    # Save training/testing images into directory train/test respectively
    saved_train_names = save_images('train', new_train)
    saved_test_names = save_images('test', test)

    # Save train_label, test_label at current working directory
    save_labels('train_label.txt', saved_train_names, new_train_label)
    save_labels('test_label.txt', saved_test_names, test_label)
