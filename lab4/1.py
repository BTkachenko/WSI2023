import tensorflow as tf
from tensorflow import keras
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score

# Wczytanie danych MNIST
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

# Przygotowanie danych
x_train = x_train.reshape(-1, 784)
x_test = x_test.reshape(-1, 784)

# Stworzenie i trening lasu decyzyjnego
forest_clf = RandomForestClassifier(n_estimators=100, random_state=42)
forest_clf.fit(x_train, y_train)

# Sprawdzenie dokładności na zbiorze testowym
y_pred = forest_clf.predict(x_test)
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy: ", accuracy)
