# -*- coding: utf-8 -*-
"""P2_IN.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1_XouiLA20B3zHW56SoEvAx-SZul_-Z9s

# Inteligencia de Negocio - Práctica 2 - Análisis Relacional mediante Segmentación

### Estudiante: <mark>LAURA LÁZARO SORALUCE</mark>
"""

!pip install hdbscan

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import time
from math import floor

from sklearn import metrics
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, AgglomerativeClustering, DBSCAN, HDBSCAN
from sklearn.mixture import GaussianMixture
from sklearn.metrics import silhouette_score, calinski_harabasz_score
from scipy.cluster.hierarchy import dendrogram, linkage
import hdbscan

sns.set(style="whitegrid")

# Detectar si se ejecuta en Colab
if 'google.colab' in str(get_ipython()):
    from google.colab import drive
    drive.mount('/content/drive')
    ruta_booking = '/content/drive/My Drive/IN/booking_Granada_2024.csv'
    ruta_alojamientos = '/content/drive/My Drive/IN/alojamientos_booking_Granada_2024.csv'
else:
    # Ruta local para VSCode u otros entornos
    ruta_booking = './booking_Granada_2024.csv'
    ruta_alojamientos = './alojamientos_booking_Granada_2024.csv'

# Leemos los dos archivos de datos
resultados_busqueda = pd.read_csv(ruta_booking, sep=';', encoding="iso-8859-1")
alojamientos_unicos = pd.read_csv(ruta_alojamientos, sep=';', encoding="iso-8859-1")

# Mostramos los datos
print("Datos de Resultados de Búsqueda:")
print(resultados_busqueda.info())
print(resultados_busqueda.head())

print("\nDatos de Alojamientos Únicos:")
print(alojamientos_unicos.info())
print(alojamientos_unicos.head())

# Resumen estadístico
print(resultados_busqueda.describe())
# Verificar valores nulos
print(resultados_busqueda.isnull().sum())

print(alojamientos_unicos.describe())
print(alojamientos_unicos.isnull().sum())

"""FUNCIONES ÚTILES Y COMUNES PARA TODOS LOS CASOS DE ESTUDIO:"""

def norm_to_zero_one(df):
    return (df - df.min()) * 1.0 / (df.max() - df.min())

#Función para evaluar los clusters
def evaluar_clusters(data, labels, nombre_algoritmo):
    if len(set(labels)) > 1:  # Sólo si hay más de un cluster
        sample_size = min(1000, len(data))  # Máx 1000 muestras si el conjunto es grande
        try:
            metric_SC = metrics.silhouette_score(data, labels, metric='euclidean', sample_size=sample_size, random_state=123456)
        except ValueError:
            metric_SC = None  # Si no se puede calcular el silhouette score
        metric_CH = metrics.calinski_harabasz_score(data, labels)

        # Imprimir resultados
        print(f"{nombre_algoritmo}:")
        if metric_SC is not None:
            print("Silhouette Coefficient: {:.5f}".format(metric_SC))
        else:
            print("Silhouette Coefficient: No calculable")
        print("Calinski-Harabasz Index: {:.3f}".format(metric_CH))
    else:
        print(f"El algoritmo {nombre_algoritmo} no pudo generar clusters válidos.")

#Función para visualizar los clusters
def graficar_clusters(data, labels, title, ax=None):
  if ax is None:
    plt.figure(figsize=(8, 6))
    ax = plt.gca()
  scatter = ax.scatter(data[:, 0], data[:, 1], c=labels, cmap='viridis', s=50)
  ax.set_title(title)
  legend1 = ax.legend(*scatter.legend_elements(), title="Clusters")
  ax.add_artist(legend1)

"""CASO DE ESTUDIO 1:

PREPROCESADO Y ELECCIÓN DE PARÁMETROS
"""

# Un set con Quality para estudios posteriores
variables_interes = ['Price', 'Rating', 'Distance', 'Review', 'Quality', 'Kitchens']
data = resultados_busqueda[variables_interes]
data = data[data['Kitchens']>0]

# Un set sin Quality para los clusters
data_subset = data[['Price', 'Rating', 'Distance', 'Review']]

# Eliminamos filas que contengan missing values
data_subset = data_subset.dropna()
data = data.dropna()

print(data_subset.describe()) # Voy mostrando los datos para analizarlos
print(data.describe())

data_scaled = data_subset.apply(norm_to_zero_one)
data = data.apply(norm_to_zero_one)

# Seleccionamos una muestra aleatoria del 10% de los datos
if len(data_subset) > 10000:
    sample_data = data_scaled.sample(frac=0.10, random_state=42)
else:
    sample_data = data_scaled

if len(data) > 10000:
    data = data.sample(frac=0.10, random_state=42)

print(sample_data.describe())

# Determinamos el número óptimo de clusters con el método del codo
inertia = []
k_range = range(2, 11)

for k in k_range:
    kmeans = KMeans(n_clusters=k, random_state=42)
    kmeans.fit(sample_data)
    inertia.append(kmeans.inertia_)

# Graficamos el método del codo
plt.figure(figsize=(8, 4))
plt.plot(k_range, inertia, marker='o')
plt.title('Método del codo - K-Means')
plt.xlabel('Número de clusters')
plt.ylabel('Inercia')
plt.grid()
plt.show()

scores = []
k_range = range(2, 11)  # Rango de clusters a probar

for k in k_range:
    clustering = AgglomerativeClustering(n_clusters=k)
    labels = clustering.fit_predict(sample_data)
    score = metrics.silhouette_score(sample_data, labels, metric='euclidean', sample_size=len(sample_data), random_state=123456)
    scores.append(score)

# Graficar el método del codo para Silhouette Score
plt.figure(figsize=(8, 4))
plt.plot(k_range, scores, marker='o')
plt.title('Método del Codo (Silhouette Score - Agglomerative Clustering)')
plt.xlabel('Número de clusters')
plt.ylabel('Silhouette Score')
plt.grid()
plt.show()

"""ALGORITMOS"""

#K-means
kmeans = KMeans(init='k-means++', n_clusters=4, n_init=5, random_state=123456)
t = time.time()
kmeans_labels = kmeans.fit_predict(sample_data)
tiempo = time.time() - t
print(f"\nTiempo de K-Means: {tiempo} segundos")

#Clustering Jerárquico
hierarchical = AgglomerativeClustering(n_clusters=3)
t = time.time()
hierarchical_labels = hierarchical.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Jerárquico: {tiempo} segundos")

#DBSCAN
dbscan = DBSCAN(eps=0.25, min_samples=8)
t = time.time()
dbscan_labels = dbscan.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de DBSCAN: {tiempo} segundos")

#Gaussian Mixture
gmm = GaussianMixture(n_components=3, random_state=123456)
t = time.time()
gmm_labels = gmm.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Gaussian Mixture: {tiempo} segundos")

#HDBSCAN
hdbscan = HDBSCAN(min_cluster_size=10, min_samples=8)
t = time.time()
hdbscan_labels = hdbscan.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de HDBSCAN: {tiempo} segundos")

pca = PCA(n_components=2)
data_reduced = pca.fit_transform(sample_data)

print("\nEvaluación de Clusters:")
evaluar_clusters(data_reduced, kmeans_labels, "K-Means")
evaluar_clusters(data_reduced, hierarchical_labels, "Clustering Jerárquico")
evaluar_clusters(data_reduced, dbscan_labels, "DBSCAN")
evaluar_clusters(data_reduced, gmm_labels, "Gaussian Mixture")
evaluar_clusters(data_reduced, hdbscan_labels, "HDBSCAN")


# Gráficos
fig, axes = plt.subplots(3, 2, figsize=(18, 12))  # 3 filas, 2 columnas
axes = axes.flatten()

# Etiquetas y títulos
labels_list = [kmeans_labels, hierarchical_labels, dbscan_labels, gmm_labels, hdbscan_labels]
titulos = ["K-Means", "Jerárquico", "DBSCAN", "Gaussian Mixture", "HDBSCAN"]

# Iteramos por los algoritmos y graficamos cada cluster
for i, (labels, titulo) in enumerate(zip(labels_list, titulos)):
    if i >= len(axes):  
        break
    graficar_clusters(data_reduced, labels, titulo, ax=axes[i])

# Eliminamos gráficos vacíos si hay menos algoritmos que subplots
for j in range(i + 1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()
plt.show()

"""INTERPRETACIÓN DE RESULTADOS"""

# Creamos una copia del DataFrame original con los clusters añadidos
clustered_data = sample_data.copy()
clustered_data = pd.concat([data[['Quality']], clustered_data], axis=1)
clustered_data = pd.concat([data[['Kitchens']], clustered_data], axis=1)

clustered_data['KMeans_Cluster'] = kmeans_labels
clustered_data['Hierarchical_Cluster'] = hierarchical_labels
clustered_data['DBSCAN_Cluster'] = dbscan_labels
clustered_data['GMM_Cluster'] = gmm_labels
clustered_data['HDBSCAN_Cluster'] = hdbscan_labels

# Obtenemos centroides del modelo K-Means
centroides = kmeans.cluster_centers_

# Calculamos la distancia euclidiana de cada punto al centroide correspondiente
clustered_data['Distancia_Centroide'] = np.linalg.norm(sample_data - centroides[kmeans_labels], axis=1)

# Promedio de distancia por cluster
distancia_promedio = clustered_data.groupby('KMeans_Cluster')['Distancia_Centroide'].mean()
print("\nDistancia promedio al centroide por cluster (K-Means):")
print(distancia_promedio)


# Relación entre los clusters y la calidad
relacion_quality = clustered_data.groupby('KMeans_Cluster')['Quality'].value_counts().unstack(fill_value=0)
print("\nRelación entre K-Means Clusters y Calidad:")
print(relacion_quality)

# Gráfico de barras apiladas para calidad
relacion_quality.plot(kind='bar', stacked=True, figsize=(10, 6))
plt.title('Relación entre Clusters y Calidad (K-Means)')
plt.xlabel('Cluster')
plt.ylabel('Número de Alojamientos')
plt.legend(title='Calidad')
plt.show()

# Calcular la matriz de correlación
correlation_matrix = data_subset.corr()

# Crear el heatmap
plt.figure(figsize=(10, 8))
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', fmt='.2f', linewidths=0.5)
plt.title('Heatmap de Correlación entre Variables')
plt.show()

# Calcular promedios por cluster
cluster_means = clustered_data.groupby('KMeans_Cluster')[['Price', 'Rating', 'Distance', 'Review']].mean()
# Crear el heatmap
plt.figure(figsize=(10, 6))
sns.heatmap(cluster_means, annot=True, cmap='YlGnBu', fmt='.2f', linewidths=0.5)
plt.title('Promedios de Características por Cluster (K-Means)')
plt.show()

# Calcular promedios por cluster
cluster_means = clustered_data.groupby('Hierarchical_Cluster')[['Price', 'Rating', 'Distance', 'Review']].mean()
# Crear el heatmap
plt.figure(figsize=(10, 6))
sns.heatmap(cluster_means, annot=True, cmap='YlGnBu', fmt='.2f', linewidths=0.5)
plt.title('Promedios de Características por Cluster (Hierarchical)')
plt.show()

# Calcular promedios por cluster
cluster_means = clustered_data.groupby('DBSCAN_Cluster')[['Price', 'Rating', 'Distance', 'Review']].mean()
# Crear el heatmap
plt.figure(figsize=(10, 6))
sns.heatmap(cluster_means, annot=True, cmap='YlGnBu', fmt='.2f', linewidths=0.5)
plt.title('Promedios de Características por Cluster (DBSCAN)')
plt.show()

# Calcular promedios por cluster
cluster_means = clustered_data.groupby('GMM_Cluster')[['Price', 'Rating', 'Distance', 'Review']].mean()
# Crear el heatmap
plt.figure(figsize=(10, 6))
sns.heatmap(cluster_means, annot=True, cmap='YlGnBu', fmt='.2f', linewidths=0.5)
plt.title('Promedios de Características por Cluster (GMM)')
plt.show()

cluster_stats = clustered_data.groupby('HDBSCAN_Cluster')[['Price', 'Rating', 'Distance', 'Review']].mean()
print("Estadísticas promedio por cluster (HDBSCAN):")
print(cluster_stats)

from pandas.plotting import scatter_matrix

# Añadir etiquetas de K-Means al dataset
scatter_data = clustered_data.copy()

# Crear el scatter plot matrix
scatter_matrix(scatter_data[variables_interes], figsize=(12, 12), diagonal='hist', alpha=0.8, c=scatter_data['KMeans_Cluster'], cmap='viridis')
plt.suptitle('Scatter Plot Matrix por Cluster (K-Means)', size=16)
plt.show()

"""CASO DE ESTUDIO 2:"""

# Variables de interés para el análisis
variables_interes = ['Type', 'Quality', 'Price', 'Location', 'Guests']
data_subset = resultados_busqueda[variables_interes]

zonas_filtradas = ['Albaicín, Granada', 'Centro de Granada, Granada']
data_filtrada = data_subset[data_subset['Location'].isin(zonas_filtradas)]

print(data_filtrada['Location'].value_counts())

data_subset = data_filtrada[['Type', 'Quality', 'Price', 'Guests']]

# Eliminamos filas que contengan valores faltantes (missing values)
data_subset = data_subset.dropna()
data_filtrada = data_filtrada.dropna()

# Descripción estadística para verificar datos
print(data_subset.describe())

# Select only numerical columns for scaling
numerical_cols = ['Price', 'Guests', 'Quality']  # Add any other numerical columns
data_scaled = data_subset[numerical_cols].apply(norm_to_zero_one)
data_filtrada2 = data_filtrada[numerical_cols].apply(norm_to_zero_one)

# Concatenate scaled numerical columns with the original non-numerical columns
data_scaled = pd.concat([data_subset[['Type']], data_scaled], axis=1)
data_filtrada2 = pd.concat([data_filtrada[['Type']], data_filtrada2], axis=1)
data_filtrada = pd.concat([data_filtrada[['Location']], data_filtrada2], axis=1)

# Selección de una muestra aleatoria del 10% de los datos si hay más de 10,000 filas
if len(data_subset) > 10000:
    sample_data = data_scaled.sample(frac=0.10, random_state=42)
else:
    sample_data = data_scaled

if len(data_filtrada) > 10000:
    data_filtrada = data_filtrada.sample(frac=0.10, random_state=42)

# Visualizar la descripción de los datos normalizados
print(sample_data.describe())

!pip install -q category_encoders
import category_encoders as ce

encoder = ce.OneHotEncoder(cols=['Type'], use_cat_names=True) # Use category names in new column names
sample_data_encoded = encoder.fit_transform(sample_data)
data_filtrada = encoder.fit_transform(data_filtrada)

X = sample_data_encoded

# Determinación del número óptimo de clusters con el método del codo
inertia = []
k_range = range(2, 11)  # Consideramos de 2 a 10 clusters

for k in k_range:
    kmeans = KMeans(n_clusters=k, random_state=42)
    kmeans.fit(X)
    inertia.append(kmeans.inertia_)

# Graficar el método del codo
plt.figure(figsize=(8, 4))
plt.plot(k_range, inertia, marker='o', color='b')
plt.title('Método del Codo (K-Means)')
plt.xlabel('Número de clusters')
plt.ylabel('Inercia')
plt.grid()
plt.show()

# Determinar los parámetros óptimos para HDBSCAN
min_cluster_size = 40  # Tamaño mínimo del clúster (puede ajustarse según el caso)
min_samples_list = [15, 20, 25, 30]  # Valores para min_samples que queremos probar

# Almacenar resultados de evaluación
resultados = []

for min_samples in min_samples_list:
    hdbscan = HDBSCAN(min_cluster_size=min_cluster_size, min_samples=min_samples)
    labels = hdbscan.fit_predict(X)

    # Excluir ruido (-1) y calcular métrica solo si hay clusters válidos
    if len(set(labels)) > 1:
        score = metrics.silhouette_score(X, labels, metric='euclidean', sample_size=min_samples, random_state=123456)
        resultados.append((min_cluster_size, min_samples, score, len(set(labels))))

# Mostrar los resultados de HDBSCAN
for min_cluster_size, min_samples, score, n_clusters in resultados:
    print(f"min_cluster_size={min_cluster_size}, min_samples={min_samples}, Silhouette={score:.3f}, Clusters={n_clusters}")

print(X.columns)

sample_data = X.copy()

#K-means
kmeans = KMeans(init='k-means++', n_clusters=3, n_init=5, random_state=123456)
t = time.time()
kmeans_labels = kmeans.fit_predict(sample_data)
tiempo = time.time() - t
print(f"\nTiempo de K-Means: {tiempo} segundos")

#Clustering Jerárquico
hierarchical = AgglomerativeClustering(n_clusters=3)
t = time.time()
hierarchical_labels = hierarchical.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Jerárquico: {tiempo} segundos")

#DBSCAN
dbscan = DBSCAN(eps=0.4, min_samples=5)
t = time.time()
dbscan_labels = dbscan.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de DBSCAN: {tiempo} segundos")

#Gaussian Mixture
gmm = GaussianMixture(n_components=2, random_state=123456)
t = time.time()
gmm_labels = gmm.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Gaussian Mixture: {tiempo} segundos")

#HDBSCAN
hdbscan = HDBSCAN(min_cluster_size=40, min_samples=25)
t = time.time()
hdbscan_labels = hdbscan.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de HDBSCAN: {tiempo} segundos")

pca = PCA(n_components=2)
data_reduced = pca.fit_transform(sample_data)

print("\nEvaluación de Clusters:")
evaluar_clusters(data_reduced, kmeans_labels, "K-Means")
evaluar_clusters(data_reduced, hierarchical_labels, "Clustering Jerárquico")
evaluar_clusters(data_reduced, dbscan_labels, "DBSCAN")
evaluar_clusters(data_reduced, gmm_labels, "Gaussian Mixture")
evaluar_clusters(data_reduced, hdbscan_labels, "HDBSCAN")


# Crear una cuadrícula para los gráficos
fig, axes = plt.subplots(3, 2, figsize=(18, 12))  # 3 filas, 2 columnas
axes = axes.flatten()  # Aplanar los ejes para iterar fácilmente

# Lista de etiquetas y títulos
labels_list = [kmeans_labels, hierarchical_labels, dbscan_labels, gmm_labels, hdbscan_labels]
titulos = ["K-Means", "Jerárquico", "DBSCAN", "Gaussian Mixture", "HDBSCAN"]

# Iterar por los algoritmos y graficar cada cluster
for i, (labels, titulo) in enumerate(zip(labels_list, titulos)):
    if i >= len(axes):  # Si hay más gráficos que subplots, detener
        break

    # Llamar a la función, pasando el eje correspondiente
    graficar_clusters(data_reduced, labels, titulo, ax=axes[i])

# Eliminar gráficos vacíos si hay menos algoritmos que subplots
for j in range(i + 1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()  # Ajustar el espacio entre gráficos
plt.show()

# Crear una copia del DataFrame original con los clusters añadidos
clustered_data = sample_data.copy()
clustered_data = pd.concat([data_filtrada[['Location']], clustered_data], axis=1)

clustered_data['KMeans_Cluster'] = kmeans_labels
clustered_data['Hierarchical_Cluster'] = hierarchical_labels
clustered_data['DBSCAN_Cluster'] = dbscan_labels
clustered_data['GMM_Cluster'] = gmm_labels
clustered_data['HDBSCAN_Cluster'] = hdbscan_labels

# Obtener centroides del modelo K-Means
centroides = kmeans.cluster_centers_

# Calcular la distancia euclidiana de cada punto al centroide correspondiente
clustered_data['Distancia_Centroide'] = np.linalg.norm(sample_data - centroides[kmeans_labels], axis=1)

# Promedio de distancia por cluster
distancia_promedio = clustered_data.groupby('KMeans_Cluster')['Distancia_Centroide'].mean()
print("\nDistancia promedio al centroide por cluster (K-Means):")
print(distancia_promedio)


# Verificar la relación entre los clusters y la calidad
relacion_quality = clustered_data.groupby('KMeans_Cluster')['Location'].value_counts().unstack(fill_value=0)
print("\nRelación entre K-Means Clusters y Ubicación:")
print(relacion_quality)

# Gráfico de barras apiladas para calidad
relacion_quality.plot(kind='bar', stacked=True, figsize=(10, 6))
plt.title('Relación entre Clusters y Ubicación (K-Means)')
plt.xlabel('Cluster')
plt.ylabel('Número de Alojamientos')
plt.legend(title='Ubicación')
plt.show()

# Boxplot para comparar precios por cluster
sns.boxplot(data=clustered_data, x='KMeans_Cluster', y='Price')
plt.title('Distribución del Precio por Cluster (K-Means)')
plt.show()

# Boxplot para guests
sns.boxplot(data=clustered_data, x='KMeans_Cluster', y='Guests')
plt.title('Distribución de la Capacidad por Cluster (K-Means)')
plt.show()

# Violin Plots para visualizar la densidad de las distribuciones en ambas zonas
plt.figure(figsize=(14, 6))

# Violin Plot de Precios
plt.subplot(1, 2, 1)
sns.violinplot(data=data_filtrada, x='Location', y='Price', palette='Set1', inner='quartile')
plt.title('Densidad de Precios por Zona')
plt.xlabel('Zona')
plt.ylabel('Precio')

# Violin Plot de Calidad
plt.subplot(1, 2, 2)
sns.violinplot(data=data_filtrada, x='Location', y='Quality', palette='Set2', inner='quartile')
plt.title('Densidad de Calidad por Zona')
plt.xlabel('Zona')
plt.ylabel('Calidad')

plt.tight_layout()
plt.show()

from sklearn.metrics import silhouette_samples

# Calcular el Silhouette Score individual para cada punto (usando DBSCAN como ejemplo)
silhouette_values = silhouette_samples(sample_data, dbscan_labels)

# Crear un DataFrame con los resultados para facilitar la visualización
silhouette_df = pd.DataFrame({
    'Silhouette Score': silhouette_values,
    'Cluster': kmeans_labels
})

# Visualización con violin plot (opcional)
plt.figure(figsize=(10, 6))
sns.violinplot(data=silhouette_df, x='Cluster', y='Silhouette Score', palette='Set3', inner='quartile')
plt.title('Distribución del Silhouette Score por Cluster (K-Means)')
plt.xlabel('Cluster')
plt.ylabel('Silhouette Score')
plt.grid(True)
plt.show()

# Sumamos los tipos de alojamiento por cluster
type_cluster_distribution = clustered_data.groupby('KMeans_Cluster').sum().filter(like='Type_')

# Gráfico apilado
type_cluster_distribution.plot(kind='bar', stacked=True, figsize=(12, 6), colormap='viridis')
plt.title("Distribución de Tipos de Alojamiento por Cluster (K-Means)")
plt.xlabel("Cluster")
plt.ylabel("Cantidad de Alojamientos")
plt.legend(title="Tipo de Alojamiento", bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.show()

# Sumamos los tipos de alojamiento por cluster
type_cluster_distribution = clustered_data.groupby('DBSCAN_Cluster').sum().filter(like='Type_')

# Gráfico apilado
type_cluster_distribution.plot(kind='bar', stacked=True, figsize=(12, 6), colormap='viridis')
plt.title("Distribución de Tipos de Alojamiento por Cluster (DBSCAN)")
plt.xlabel("Cluster")
plt.ylabel("Cantidad de Alojamientos")
plt.legend(title="Tipo de Alojamiento", bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.show()

"""CASO DE ESTUDIO 3:

PREPROCESAMIENTO DE DATOS
"""

from sklearn.cluster import OPTICS

# Selección de columas relevantes
variables_interes = ['Price', 'Distance', 'Ranking position', 'Type', 'Rating']
data_clustering = resultados_busqueda[variables_interes]

data_clustering = data_clustering[data_clustering['Ranking position'].between(1,170)]
data_clustering = data_clustering[data_clustering['Rating']>5]

data_subset = data_clustering[['Price', 'Distance', 'Ranking position', 'Type']]

# Revisión inicial
print(data_clustering.info())
print(data_clustering.describe())

# Manejo de nulos
data_clustering = data_clustering.dropna()
data_subset = data_subset.dropna()

numerical_cols = ['Price', 'Distance', 'Ranking position', 'Rating']
data_clustering[numerical_cols] = data_clustering[numerical_cols].apply(norm_to_zero_one)
numerical_cols = ['Price', 'Distance', 'Ranking position']
data_subset[numerical_cols] = data_subset[numerical_cols].apply(norm_to_zero_one)

# Selección de una muestra aleatoria del 10% de los datos si hay más de 10,000 filas
if len(data_subset) > 10000:
    sample_data = data_subset.sample(frac=0.10, random_state=42)
else:
    sample_data = data_scaled

if len(data_clustering) > 10000:
    data_clustering = data_clustering.sample(frac=0.10, random_state=42)

# Visualizar la descripción de los datos normalizados
print(sample_data.describe())

encoder = ce.OneHotEncoder(cols=['Type'], use_cat_names=True) # Use category names in new column names
sample_data_encoded = encoder.fit_transform(sample_data)
data_clustering = encoder.fit_transform(data_clustering)

X = sample_data_encoded

# Determinación del número óptimo de clusters con el método del codo
inertia = []
k_range = range(2, 11)  # Consideramos de 2 a 10 clusters

for k in k_range:
    kmeans = KMeans(n_clusters=k, random_state=42)
    kmeans.fit(X)
    inertia.append(kmeans.inertia_)

# Graficar el método del codo
plt.figure(figsize=(8, 4))
plt.plot(k_range, inertia, marker='o', color='b')
plt.title('Método del Codo (K-Means)')
plt.xlabel('Número de clusters')
plt.ylabel('Inercia')
plt.grid()
plt.show()

xi_list= [0.2, 0.4, 0.6, 0.8]
for xi in xi_list:
    optics_model = OPTICS(min_samples=20, xi=xi, min_cluster_size=20)
    labels = optics_model.fit_predict(X)

    score = metrics.silhouette_score(X, labels, metric='euclidean', sample_size=len(X), random_state=123456)
    print(f"xi={xi}, Silhouette={score:.3f}")

sample_data = X.copy()

#K-means
kmeans = KMeans(init='k-means++', n_clusters=3, n_init=5, random_state=123456)
t = time.time()
kmeans_labels = kmeans.fit_predict(sample_data)
tiempo = time.time() - t
print(f"\nTiempo de K-Means: {tiempo} segundos")

#Clustering Jerárquico
hierarchical = AgglomerativeClustering(n_clusters=3)
t = time.time()
hierarchical_labels = hierarchical.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Jerárquico: {tiempo} segundos")

#DBSCAN
#dbscan = DBSCAN(eps=0.4, min_samples=5)
#t = time.time()
#dbscan_labels = dbscan.fit_predict(sample_data)
#tiempo = time.time() - t
#print(f"Tiempo de DBSCAN: {tiempo} segundos")

#OPTICS
optics_model = OPTICS(min_samples=15, xi=0.18, min_cluster_size=15)
t = time.time()
optics_labels = optics_model.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de OPTICS: {tiempo} segundos")

#Gaussian Mixture
gmm = GaussianMixture(n_components=2, random_state=123456)
t = time.time()
gmm_labels = gmm.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Gaussian Mixture: {tiempo} segundos")

#HDBSCAN
#hdbscan = HDBSCAN(min_cluster_size=40, min_samples=25)
#t = time.time()
#hdbscan_labels = hdbscan.fit_predict(sample_data)
#tiempo = time.time() - t
#print(f"Tiempo de HDBSCAN: {tiempo} segundos")

from sklearn.cluster import Birch

#Birch
birch_model = Birch(n_clusters=2)
t = time.time()
birch_labels = birch_model.fit_predict(sample_data)
tiempo = time.time() - t
print(f"Tiempo de Birch: {tiempo} segundos")

pca = PCA(n_components=2)
data_reduced = pca.fit_transform(sample_data)

print("\nEvaluación de Clusters:")
evaluar_clusters(data_reduced, kmeans_labels, "K-Means")
evaluar_clusters(data_reduced, hierarchical_labels, "Clustering Jerárquico")
evaluar_clusters(data_reduced, optics_labels, "OPTICS")
no_noise_mask = optics_labels != -1
X_no_noise = sample_data[no_noise_mask]
labels_no_noise = optics_labels[no_noise_mask]
evaluar_clusters(X_no_noise, labels_no_noise, "OPTICS_No_Noise")
evaluar_clusters(data_reduced, gmm_labels, "Gaussian Mixture")
evaluar_clusters(data_reduced, birch_labels, "Birch")


# Crear una cuadrícula para los gráficos
fig, axes = plt.subplots(3, 2, figsize=(18, 12))  # 3 filas, 2 columnas
axes = axes.flatten()  # Aplanar los ejes para iterar fácilmente

# Lista de etiquetas y títulos
labels_list = [kmeans_labels, hierarchical_labels, optics_labels, labels_no_noise, gmm_labels, birch_labels]
titulos = ["K-Means", "Jerárquico", "OPTICS", "OPTICS_No_Noise", "Gaussian Mixture", "Birch"]

# Iterar por los algoritmos y graficar cada cluster
for i, (labels, titulo) in enumerate(zip(labels_list, titulos)):
    if i >= len(axes):  # Si hay más gráficos que subplots, detener
        break

    # Llamar a la función, pasando el eje correspondiente
    if titulo == "OPTICS_No_Noise":
      graficar_clusters(X_no_noise.to_numpy(), labels, titulo, ax=axes[i])
    else:
      graficar_clusters(data_reduced, labels, titulo, ax=axes[i])

# Eliminar gráficos vacíos si hay menos algoritmos que subplots
for j in range(i + 1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()  # Ajustar el espacio entre gráficos
plt.show()

clustered_data = sample_data.copy()
clustered_data = pd.concat([data_clustering[['Rating']], clustered_data], axis=1)

clustered_data['KMeans_Cluster'] = kmeans_labels
clustered_data['Hierarchical_Cluster'] = hierarchical_labels
clustered_data['OPTICS_Cluster'] = optics_labels
clustered_data['GaussianMixture_Cluster'] = gmm_labels
clustered_data['Birch_Cluster'] = birch_labels

centroides = kmeans.cluster_centers_
clustered_data['Distancia_Centroide'] = np.linalg.norm(sample_data - centroides[kmeans_labels], axis=1)

# Promedio de distancia por cluster
distancia_promedio = clustered_data.groupby('KMeans_Cluster')['Distancia_Centroide'].mean()
print("\nDistancia promedio al centroide por cluster (K-Means):")
print(distancia_promedio)

# Promedio de variables por cluster
promedios_por_cluster = clustered_data.groupby('KMeans_Cluster')[['Price', 'Rating', 'Distance', 'Ranking position']].mean()
print("\nPromedio de variables por cluster:")
print(promedios_por_cluster)

sns.boxplot(data=clustered_data, x='KMeans_Cluster', y='Ranking position')
plt.title('Distribución del Ranking por Cluster (K-Means)')
plt.show()

# Calcular el Silhouette Score individual para K-Means
silhouette_values = silhouette_samples(sample_data, kmeans_labels)

# Crear un DataFrame con los resultados
silhouette_df = pd.DataFrame({
    'Silhouette Score': silhouette_values,
    'Cluster': kmeans_labels
})

# Visualización
sns.violinplot(data=silhouette_df, x='Cluster', y='Silhouette Score', palette='Set3', inner='quartile')
plt.title('Distribución del Silhouette Score por Cluster (K-Means)')
plt.xlabel('Cluster')
plt.ylabel('Silhouette Score')
plt.grid(True)
plt.show()

# Comparar promedios de variables por cluster para diferentes algoritmos
promedios_optics = clustered_data.groupby('OPTICS_Cluster')[['Price', 'Rating', 'Distance', 'Ranking position']].mean()

print("\nPromedios OPTICS:")
print(promedios_optics)

sns.boxplot(data=clustered_data, x='KMeans_Cluster', y='Ranking position')
plt.title('Distribución del Ranking por Cluster (K-Means)')
plt.show()

# Relación entre clusters de GMM y variables de interés
gmm_cluster_summary = clustered_data.groupby('GaussianMixture_Cluster')[['Rating', 'Ranking position', 'Price', 'Distance']].mean()

print("\nPromedios de variables por cluster (Gaussian Mixture):")
print(gmm_cluster_summary)

# Visualización: Boxplot de Rating por Cluster
sns.boxplot(data=clustered_data, x='GaussianMixture_Cluster', y='Rating', palette='Set2')
plt.title('Distribución del Rating por Cluster (Gaussian Mixture)')
plt.xlabel('Cluster')
plt.ylabel('Rating')
plt.show()

# Boxplot para Ranking position por Cluster
sns.boxplot(data=clustered_data, x='GaussianMixture_Cluster', y='Ranking position', palette='coolwarm')
plt.title('Distribución del Ranking por Cluster (Gaussian Mixture)')
plt.xlabel('Cluster')
plt.ylabel('Ranking position')
plt.show()

# Iterar por cada cluster en los datos
for cluster in clustered_data['GaussianMixture_Cluster'].unique():
    cluster_data = clustered_data[clustered_data['GaussianMixture_Cluster'] == cluster]

    # Calcular la matriz de correlación para las variables de interés
    corr_matrix = cluster_data[['Rating', 'Ranking position', 'Price', 'Distance']].corr()

    # Graficar el heatmap
    plt.figure(figsize=(6, 4))
    sns.heatmap(corr_matrix, annot=True, cmap='coolwarm', fmt=".2f")
    plt.title(f"Heatmap de Correlaciones - Cluster {cluster} (Gaussian Mixture)")
    plt.show()

plt.figure(figsize=(12, 8))

# Gráfico de burbujas
sns.scatterplot(
    data=clustered_data,
    x='Ranking position',
    y='Rating',
    size='Price',
    hue='GaussianMixture_Cluster',
    palette='viridis',
    alpha=0.7,
    sizes=(50, 500)  # Tamaño mínimo y máximo de las burbujas
)

# Configuración de la gráfica
plt.title('Relación entre Ranking, Rating y Precio (Clusters Gaussian Mixture)')
plt.xlabel('Ranking position')
plt.ylabel('Rating')
plt.legend(title='Cluster', loc='upper right', bbox_to_anchor=(1.2, 1))
plt.grid(True)
plt.tight_layout()
plt.show()