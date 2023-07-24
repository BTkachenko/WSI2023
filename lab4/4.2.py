import numpy as np
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from tensorflow.keras.datasets import mnist

# Pobranie danych MNIST
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Przekształcenie obrazów do jednowymiarowych wektorów
x_train = x_train.reshape(len(x_train), -1)
x_test = x_test.reshape(len(x_test), -1)

# Normalizacja danych
x_train = StandardScaler().fit_transform(x_train)

# Redukcja wymiarowości za pomocą PCA
pca = PCA(n_components=50)
x_train = pca.fit_transform(x_train)

# Ustalenie parametrów DBSCAN
eps = 10.0
min_samples = 5

# Utworzenie instancji DBSCAN i dopasowanie do danych
db = DBSCAN(eps=eps, min_samples=min_samples).fit(x_train)

# Pobranie etykiet klastrów
labels = db.labels_

# Obliczenie liczby klastrów (ignorując szum)
n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
n_noise = list(labels).count(-1)

print('Estimated number of clusters: %d' % n_clusters)
print('Estimated number of noise points: %d' % n_noise)

if n_clusters > 0:
    # Przypisanie etykiety do każdego klastra na podstawie najczęstszej prawdziwej etykiety w klastrze
    cluster_labels = []
    for cluster in range(n_clusters):
        true_labels = y_train[labels == cluster]
        most_common = np.bincount(true_labels).argmax()
        cluster_labels.append(most_common)

    # Obliczenie dokładności klasyfikacji
    accuracy = np.sum([1 for true, pred in zip(y_train, labels) if true == cluster_labels[pred]]) / len(y_train)
    print('Accuracy: %.2f' % accuracy)
else:
    print("No clusters found. Try adjusting DBSCAN parameters.")


