from sklearn import datasets
import h5py

def save_data(data_function, filename):
    #load data
    data = data_function()
    X = data.data
    y = data.target

    #save to file
    hf = h5py.File(filename+'.h5', 'w')
    hf.create_dataset('X', data=X)
    hf.create_dataset('y', data=y)
    hf.close()

if __name__ == "__main__":
    save_data(datasets.load_iris, "iris")
    save_data(datasets.load_boston, "boston")
    save_data(datasets.load_diabetes, "diabetes")
    save_data(datasets.load_digits, "digits")

    save_data(datasets.load_linnerud, "linnerud")
    save_data(datasets.load_wine, "wine")
    save_data(datasets.load_breast_cancer, "breast_cancer")

