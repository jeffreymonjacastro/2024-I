Vamos a crear un proyecto en React Native que utiliza el mismo API que nuestro proyecto anterior de react. Seguimos los siguientes pasos.

### Requisitos

- Node.js: https://nodejs.org/
- npm: https://nodejs.org/
- Expo Go (en tu dispositivo móvil): https://expo.dev/client


### Instrucciones

Al final de cada paso asegurate de que tu aplicación funciona correctamente.

Puedes Correr tu proyecto con el siguiente comando:

```bash
npx expo start
```

Sigue las instrucciones en la consola para abrir la aplicación en tu dispositivo móvil.

### Paso 1: Set up

React Native es un framework de desarrollo de aplicaciones móviles que permite a los desarrolladores crear aplicaciones móviles multiplataforma utilizando JavaScript y React. Expo es una plataforma de open source para crear aplicaciones universales con React Native.

Utilizamos el siguiente comando para crear un proyecto-ejemplo.

```bash
npx create-expo-app --template   
```

Elegimos **blank** y le damos un nombre a nuestro proyecto.

```bash
cd ReactNativeProject
```

Instalamos las dependencias necesarias:

```bash
npm install
```

Abrimos el proyecto en VS code.

Probamos la aplicación en nuestro dispositivo móvil con Expo Go.

### Paso 2: Implementación de componentes básicos: View, ScrollView, Text, TextInput, Image.

Los componentes básicos de React Native son similares a los de React. Sin embargo, en lugar de usar HTML, usamos componentes de React Native como `View`, `Text`, `TextInput`, `Image`, etc.

Estos componentes se utilizan para construir la interfaz de usuario de la aplicación. Por ejemplo `View` se utiliza para contener otros componentes, `Text` se utiliza para mostrar texto, `TextInput` se utiliza para la entrada de texto, `Image` se utiliza para mostrar imágenes, etc.

Modificamos el archivo `App.js` para que se vea de la siguiente manera:

```javascript
import { StyleSheet, View } from 'react-native';
import LoginScreen from './src/LoginScreen';
import RegisterScreen from './src/RegisterScreen';

export default function App() {
  return (
    <View style={styles.container}>
      <LoginScreen />
      <RegisterScreen />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
```

Creamos un nuevo archivo llamado `LoginScreen.js` en el directorio `src`:

```javascript
// src/LoginScreen.js
import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';

const LoginScreen = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  return (
    <View style={styles.container}>
      <Text>Email:</Text>
      <TextInput
        style={styles.input}
        value={email}
        onChangeText={setEmail}
        placeholder="Enter your email"
      />
      <Text>Password:</Text>
      <TextInput
        style={styles.input}
        value={password}
        onChangeText={setPassword}
        placeholder="Enter your password"
        secureTextEntry
      />
      <Button title="Login" />
      <Button
        title="Go to Register"
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    padding: 16,
  },
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 12,
    paddingHorizontal: 8,
  },
});

export default LoginScreen;
```

Creamos un nuevo archivo llamado `RegisterScreen.js` en el directorio `src`:

```javascript
// src/RegisterScreen.js
import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet, TouchableOpacity } from 'react-native';

const RegisterScreen = () => {
  const [name, setName] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [isTeacher, setIsTeacher] = useState(false);

  const toggleCheckbox = () => {
    setIsTeacher(!isTeacher);
  };

  return (
    <View style={styles.container}>
      <Text>Name:</Text>
      <TextInput
        style={styles.input}
        value={name}
        onChangeText={setName}
        placeholder="Enter your name"
      />
      <Text>Email:</Text>
      <TextInput
        style={styles.input}
        value={email}
        onChangeText={setEmail}
        placeholder="Enter your email"
      />
      <Text>Password:</Text>
      <TextInput
        style={styles.input}
        value={password}
        onChangeText={setPassword}
        placeholder="Enter your password"
        secureTextEntry
      />
      <View style={styles.checkboxContainer}>
        <TouchableOpacity onPress={toggleCheckbox} style={styles.checkbox}>
          {isTeacher && <View style={styles.checked} />}
        </TouchableOpacity>
        <Text style={styles.checkboxLabel}>Are you a teacher?</Text>
      </View>
      <Button title="Register" />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    padding: 16,
  },
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 12,
    paddingHorizontal: 8,
  },
  checkboxContainer: {
    flexDirection: 'row',
    alignItems: 'center',
    marginBottom: 12,
  },
  checkbox: {
    width: 20,
    height: 20,
    borderWidth: 1,
    borderColor: 'gray',
    marginRight: 8,
    justifyContent: 'center',
    alignItems: 'center',
  },
  checked: {
    width: 12,
    height: 12,
    backgroundColor: 'blue',
  },
  checkboxLabel: {
    fontSize: 16,
  },
});

export default RegisterScreen;
```

### Paso 3: Expo Router (Navigator)

Para esta parte vamos a usar React Navigation. 

Necesitaremos los siguiente sub componentes, `@react-navigation/native` y `@react-navigation/stack`. Estos componentes nos permiten navegar entre pantallas en nuestra aplicación.

Instala React Navigation:

```bash
npm install @react-navigation/native @react-navigation/stack
```

Modifica el archivo `App.js` para agregar la navegación:

```javascript
import LoginScreen from './src/LoginScreen';
import RegisterScreen from './src/RegisterScreen';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

const Stack = createStackNavigator();

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator initialRouteName="Login">
        <Stack.Screen name="Login" component={LoginScreen}/>
        <Stack.Screen name="Register" component={RegisterScreen} />
      </Stack.Navigator>
    </NavigationContainer>
  );
}
```

Realiza las siguientes modificaciones en los archivos `LoginScreen.js` y `RegisterScreen.js` para que funcionen con la navegación:

```javascript
// src/LoginScreen.js

//.
//.
//.

const LoginScreen = ({navigation}) => {

//.
//.
//.
        <Button
        title="Go to Register"
        onPress={() => navigation.navigate('Register')}
      />

//.
//.
//.
```

```javascript
// src/RegisterScreen.js

//.
//.
//.

const RegisterScreen = ({navigation}) => {

//.
//.
//.

      <Button title="Register" />
      <Button
        title="Go to Login"
        onPress={() => navigation.navigate('Login')}
      />

//.
//.
//.
```

### Paso 4: Configuración de Axios para realizar llamadas a APIs REST.

Axios como vimos la semana pasada, es una librería de JavaScript que se utiliza para realizar peticiones HTTP desde el navegador o desde Node.js. En React Native, Axios se puede utilizar para realizar peticiones HTTP a un servidor RESTful.

Instala Axios:

```bash
npm install axios
```

Crea un archivo llamado `api.js` en el directorio `src`:

```javascript
// src/api.js

import axios from 'axios';

const API_URL = 'http://52.3.234.203:8080'; 

export const register = async (name, email, password, isTeacher) => {
  const response = await axios.post(`${API_URL}/auth/register`, { name, email, password, isTeacher });
  return response.data;
};
```

Modifica el archivo `RegisterScreen.js` para que utilice la función `register`:

```javascript
// src/RegisterScreen.js

//.
//.
//.

import { View, Text, TextInput, Button, StyleSheet, TouchableOpacity } from 'react-native';
import { register } from './api';

//.
//.
//.

  const [isTeacher, setIsTeacher] = useState(false);

  const handleRegister = async () => {
    try {
      await register(name, email, password, isTeacher);
      navigation.navigate('Login');
    } catch (error) {
      console.error('Registration failed', error);
    }
  };

//.
//.
//.

      <Button title="Register" onPress={handleRegister} />

//.
//.
//.
```


### Paso 5: Implementación de flujos de autenticación y manejo de tokens JWT usando AsyncStorage.

AsyncStorage es una API de almacenamiento persistente simple y sin cifrado para React Native. Se utiliza para almacenar datos en el dispositivo del usuario de forma persistente.

Instala AsyncStorage:

```bash
npm install @react-native-async-storage/async-storage
```

Modifica el archivo `api.js` para que utilice AsyncStorage:

```javascript
import axios from 'axios';
import AsyncStorage from '@react-native-async-storage/async-storage';

const API_URL = 'http://52.3.234.203:8080'; 

export const login = async (email, password) => {
  const response = await axios.post(`${API_URL}/auth/login`, { email, password });
  await AsyncStorage.setItem('token', response.data.token); // Store token
  return response.data;
};

export const register = async (name, email, password, isTeacher) => {
  const response = await axios.post(`${API_URL}/auth/register`, { name, email, password, isTeacher });
  return response.data;
};

export const listCourses = async () => {
  const token = await AsyncStorage.getItem('token'); // Retrieve token
  const response = await axios.get(`${API_URL}/course`, {
    headers: {
      Authorization: `Bearer ${token}`,
    },
  });
  return response.data;
};

export const logout = async () => {
  await AsyncStorage.removeItem('token'); // Remove token
};
```

Modifica el archivo `LoginScreen.js` para que utilice la función `login`:

```javascript
// src/LoginScreen.js

//.
//.
//.

import { View, Text, TextInput, Button, StyleSheet } from 'react-native';
import { login } from './api';

const LoginScreen = ({ navigation, setIsLoggedIn }) => {

//.
//.
//.

  const handleLogin = async () => {
    try {
      await login(email, password);
      setIsLoggedIn(true);
    } catch (error) {
      console.error('Login failed', error);
    }
  };

//.
//.
//.

      <Button title="Login" onPress={handleLogin} />

//.
//.
//.
```

Instala la librería de navegación de pestañas:

```bash
npm install @react-navigation/bottom-tabs
```

Modifica el archivo `App.js` para que utilice el estado `isLoggedIn`:



```javascript
import React, { useState } from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import LoginScreen from './src/LoginScreen';
import RegisterScreen from './src/RegisterScreen';
import CoursesScreen from './src/CoursesScreen';

const Stack = createStackNavigator();
const Tab = createBottomTabNavigator();

const AuthStack = ({ setIsLoggedIn }) => (
  <Stack.Navigator initialRouteName="Login">
    <Stack.Screen name="Login">
      {props => <LoginScreen {...props} setIsLoggedIn={setIsLoggedIn} />}
    </Stack.Screen>
    <Stack.Screen name="Register" component={RegisterScreen} />
  </Stack.Navigator>
);

const AppTabs = ({ setIsLoggedIn }) => (
  <Tab.Navigator initialRouteName='Courses'>
    <Tab.Screen name="Courses">
      {props => <CoursesScreen {...props} setIsLoggedIn={setIsLoggedIn} />}
    </Tab.Screen>
  </Tab.Navigator>
);

const App = () => {
  const [isLoggedIn, setIsLoggedIn] = useState(false);

  return (
    <NavigationContainer>
      {isLoggedIn ? <AppTabs setIsLoggedIn={setIsLoggedIn} /> : <AuthStack setIsLoggedIn={setIsLoggedIn}/>}
    </NavigationContainer>
  	);
};

export default App;
```

Crea un nuevo archivo llamado `CoursesScreen.js` en el directorio `src`:

```javascript
import React, { useEffect, useState } from 'react';
import { View, Text, FlatList, StyleSheet, Button } from 'react-native';
import { listCourses, logout } from './api';

const CoursesScreen = ({ setIsLoggedIn }) => {
  const [courses, setCourses] = useState([]);

  useEffect(() => {
    const fetchCourses = async () => {
      try {
        const data = await listCourses();
        setCourses(data);
      } catch (error) {
        console.error('Failed to fetch courses', error);
      }
    };

    fetchCourses();
  }, []);

  const handleLogout = async () => {
    await logout();
    setIsLoggedIn(false);
  };

  return (
    <View style={styles.container}>
      <Text>Courses:</Text>
      <FlatList
        data={courses}
        keyExtractor={(item) => item.id.toString()}
        renderItem={({ item }) => (
          <View style={styles.courseItem}>
            <Text>{item.title}</Text>
            <Text>{item.remainingSpots}</Text>
          </View>
        )}
      />
      <Button title="Logout" onPress={handleLogout} />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 16,
  },
  courseItem: {
    padding: 16,
    borderBottomWidth: 1,
    borderBottomColor: '#ccc',
  },
});

export default CoursesScreen;
```

### Paso 6: Uso de Expo Secure Store para el almacenamiento seguro de tokens y credenciales.

Secure Store es una API de almacenamiento seguro para React Native que se utiliza para almacenar datos sensibles de forma segura en el dispositivo del usuario. Secure Store cifra los datos antes de almacenarlos en el dispositivo y los descifra cuando se recuperan.

Para los proyectos, deberán utilizar secure storage para el guardado de tokens y credenciales.

Instala Expo Secure Store:

```bash
npx expo install expo-secure-store
```

Modifica el archivo `api.js` para que utilice Secure Store:

```javascript
import axios from 'axios';
import * as SecureStore from 'expo-secure-store';

const API_URL = 'http://52.3.234.203:8080'; 

export const login = async (email, password) => {
  const response = await axios.post(`${API_URL}/auth/login`, { email, password });
  await SecureStore.setItemAsync('token', response.data.token); // Store token securely
  return response.data;
};

export const register = async (name, email, password, isTeacher) => {
  const response = await axios.post(`${API_URL}/auth/register`, { name, email, password, isTeacher });
  return response.data;
};

export const listCourses = async () => {
  const token = await SecureStore.getItemAsync('token'); // Retrieve token securely
  const response = await axios.get(`${API_URL}/course`, {
    headers: {
      Authorization: `Bearer ${token}`,
    },
  });
  return response.data;
};

export const logout = async () => {
  await SecureStore.deleteItemAsync('token'); // Remove token securely
};
```

### Paso 7: Implementación de notificaciones push en eventos específicos de la aplicación.

Las notificaciones push son mensajes que se envían a los dispositivos móviles de los usuarios para informarles sobre eventos específicos de la aplicación. Las notificaciones push pueden ser enviadas por el servidor de la aplicación a los dispositivos móviles de los usuarios en tiempo real.

En este ejemplo vamos a enviar una notificación push cuando el usuario inicie sesión en la aplicación. 

Otros casos pueden ser cuando un usuario reciba un mensaje, cuando un usuario reciba una solicitud de amistad, etc.

Instala Expo Notifications:

```bash
npx expo install expo-notifications
```

Crea un archivo llamado `notificationHelper.js` en el directorio `src`:

```javascript
// src/notificationHelper.js
import * as Notifications from 'expo-notifications';

export const requestPermissions = async () => {
    const { status } = await Notifications.requestPermissionsAsync();
    if (status !== 'granted') {
      alert('You need to enable notifications to use this app.');
    }
}

// Configure notification handling
Notifications.setNotificationHandler({
  handleNotification: async () => ({
    shouldShowAlert: true,
    shouldPlaySound: false,
    shouldSetBadge: false,
  }),
});

export const scheduleNotification = async (title, body) => {
  await Notifications.scheduleNotificationAsync({
    content: {
      title,
      body,
    },
    trigger: { seconds: 1 },
  });
};
```

Modifica el archivo `LoginScreen.js` para que utilice las funciones de notificación:

```javascript
// src/LoginScreen.js
import React, { useState, useEffect } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';
import { login } from './api';
import { requestPermissions, scheduleNotification } from './notificationHelper';

const LoginScreen = ({ navigation, setIsLoggedIn }) => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  useEffect(() => {
    requestPermissions();
  }, []);

  const handleLogin = async () => {
    try {
      await login(email, password);
      await scheduleNotification('Login Successful', 'You have successfully logged in.');
      setIsLoggedIn(true);
    } catch (error) {
      console.error('Login failed', error);
 
//.
//.
//.
```

### Paso 8: Entender que son Expo-Sensors y cómo implementarlos.

Expo Sensors es una API de sensores para React Native que se utiliza para acceder a los sensores del dispositivo móvil, como el acelerómetro, el giroscopio, el magnetómetro, etc. Expo Sensors proporciona una interfaz sencilla para acceder a los datos de los sensores del dispositivo móvil y utilizarlos en la aplicación.

Otros sensores más comunes son el uso de la cámara, el micrófono, el y el GPS. Recuerden que para el uso de estos sensores, se debe solicitar permisos al usuario. En sus proyectos, deberán utilizar 2 o más sensores.

Instala Expo Sensors:

```bash
npx expo install expo-sensors
```

Modificamos el archivo `App.js` para agregar el tab de sensores:

```javascript
import LoginScreen from './src/LoginScreen';
import RegisterScreen from './src/RegisterScreen';
import CoursesScreen from './src/CoursesScreen';
import SensorScreen from './src/SensorScreen';

const Stack = createStackNavigator();
const Tab = createBottomTabNavigator();

//.
//.
//.

    <Tab.Screen name="Courses">
      {props => <CoursesScreen {...props} setIsLoggedIn={setIsLoggedIn} />}
    </Tab.Screen>
    <Tab.Screen name="Sensor" component={SensorScreen} />
  </Tab.Navigator>
);

//.
//.
//.
```

Crea un nuevo archivo llamado `SensorScreen.js` en el directorio `src`:

```javascript
// src/SensorScreen.js
import React, { useState, useEffect } from 'react';
import { View, Text, Button, StyleSheet } from 'react-native';
import { Accelerometer } from 'expo-sensors';

const SensorScreen = ({ navigation }) => {
  const [data, setData] = useState({
    x: 0,
    y: 0,
    z: 0,
  });
  const [subscription, setSubscription] = useState(null);

  const _subscribe = () => {
    setSubscription(
      Accelerometer.addListener(accelerometerData => {
        setData(accelerometerData);
      })
    );
    Accelerometer.setUpdateInterval(100); // Set update interval to 0.1 second
  };

  const _unsubscribe = () => {
    subscription && subscription.remove();
    setSubscription(null);
  };

  useEffect(() => {
    _subscribe();
    return () => _unsubscribe();
  }, []);

  return (
    <View style={styles.container}>
      <Text style={styles.text}>Accelerometer Data:</Text>
      <Text style={styles.data}>
        x: {data.x.toFixed(2)} y: {data.y.toFixed(2)} z: {data.z.toFixed(2)}
      </Text>
      <Button title="Unsubscribe" onPress={_unsubscribe} />
      <Button title="Go Back" onPress={() => navigation.goBack()} />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 16,
  },
  text: {
    fontSize: 18,
    marginBottom: 10,
  },
  data: {
    fontSize: 16,
    marginBottom: 20,
  },
});

export default SensorScreen;
```

### Final

¡Felicidades! Has completado el proyecto de React Native. Ahora puedes ejecutar tu aplicación en tu dispositivo móvil y probarla.

```bash
npx expo start
```

Sigue las instrucciones en la consola para abrir la aplicación en tu dispositivo móvil.

¡Gracias por seguir este tutorial! Espero que hayas aprendido algo nuevo y emocionante. Si tienes alguna pregunta, no dudes en preguntar
en el canal de Discord o directamente a través de mi correo electrónico.
