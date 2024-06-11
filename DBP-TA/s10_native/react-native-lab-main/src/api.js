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