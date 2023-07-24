import tensorflow as tf
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import DBSCAN
from sklearn.metrics import accuracy_score, adjusted_rand_score

# Wczytanie danych MNIST
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

# Przygotowanie danych
x_train = x_train.reshape(-1, 784) / 255.0
x_test = x_test.reshape(-1, 784) / 255.0

# Skalowanie cech
scaler = StandardScaler()
x_train = scaler.fit_transform(x_train)
x_test = scaler.transform(x_test)

# PCA
pca = PCA(n_components=2)
x_train_pca = pca.fit_transform(x_train)
x_test_pca = pca.transform(x_test)

# DBSCAN
eps = 0.5
min_samples = 10
db = DBSCAN(eps=eps, min_samples=min_samples)
db.fit(x_train_pca)

# Etykiety klastrów dla każdego punktu w zbiorze danych
labels = db.labels_

# Liczba klastrów w etykietach, ignorując szum w razie wystąpienia
n_clusters_ = len(set(labels)) - (1 if -1 in labels else 0)
n_noise_ = list(labels).count(-1)

print('Estimated number of clusters: %d' % n_clusters_)
print('Estimated number of noise points: %d' % n_noise_)

# Predykcja na zbiorze testowym
clusters = db.fit_predict(x_test_pca)

# Procent szumu
noise_percentage = (clusters == -1).sum() / len(clusters) * 100
print("Procent szumu:", noise_percentage)

# Dokładność i ARI
print("Dokładność:", accuracy_score(y_test, clusters))
print("ARI:", adjusted_rand_score(y_test, clusters))
