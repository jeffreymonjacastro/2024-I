import axios from 'axios'

export const BACKEND_URL = 'http://localhost:8080';


export const fetchLogin = async(email, password) => {
  // BodyRequest
  const response = await axios.post(`${BACKEND_URL}/auth/login`, {email, password})

  return response
}

export const fetchRides = async(page) => {
  // ParamVariable
  const response = await axios.get(`${BACKEND_URL}/ride/user?page=${page}&size=10`,{
    headers: {
      'Authorization': `Bearer ${localStorage.getItem('token')}`,
    },
  })

  return response

}

export const deleteRide = async(rideId) => {

  // Path
  const response = await axios.delete(`${BACKEND_URL}/ride/${rideId}`, {
    headers: {
      'Authorization': `Bearer ${localStorage.getItem('token')}`,
    }
  })

  return response
} 