import axios from 'axios'

const BACKEND_URL = 'http://localhost:8080'

export const fetchLogin = async(email, password) => {
  const data = {
    email,
    password
  }

  const response = await axios.post(`${BACKEND_URL}/auth/login`, data)

  return response
}

export const getRides = async(page, size) => {
  const response = await axios.get(`${BACKEND_URL}/ride/user?page=${page}&size=${size}`, {
    headers: {
      'Authorization': `Bearer ${localStorage.getItem('token')}`
    }
  })

  return response
}