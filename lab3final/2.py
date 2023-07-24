import os
import cv2
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

def gen_my_test_data():
    directory = 'images'
    y = [i for _ in range(4) for i in range(10)]
    x = []
    for filename in sorted(os.listdir(directory)):
        if filename.endswith(".png"):
            img = cv2.imread(os.path.join(directory, filename), cv2.IMREAD_GRAYSCALE)
            img = cv2.resize(img, (28, 28))
            img = img / 255.0
            img = np.array(img)
            x.append(img)
    return np.array(x), np.asarray(y)

my_test_x, my_test_y = gen_my_test_data()

# Display some of your images
for i in range(5):
    plt.imshow(my_test_x[i], cmap='gray')
    plt.show()

# Load MNIST dataset
mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Preprocess the data
x_train, x_test = x_train / 255.0, x_test / 255.0

# Define the neural network architecture
model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape=(28, 28)),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dropout(0.2),  # Add dropout layer
    tf.keras.layers.Dense(10, activation='softmax')
])

# Compile the model
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Train the model
model.fit(x_train, y_train, epochs=10)  # Increase number of epochs

# Evaluate the model
test_loss, test_acc = model.evaluate(x_test, y_test)
print(f"Standard Test accuracy: {test_acc}")

test_loss, test_acc = model.evaluate(my_test_x, my_test_y)
print(f"My Test accuracy: {test_acc}")



