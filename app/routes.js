import React from 'react';
import { Text, View, Image, StyleSheet } from 'react-native';

import { StackNavigator, TabNavigator } from 'react-navigation';

import CitiesTab from './tabs/Cities/CitiesTab';
// import AddCityTab from './tabs/AddCity/AddCityTab';
import tabAddCity from '../lib/js/re/tabAddCity';

// TODO move somewhere else
import { addCity, updateAsyncStorage } from './actions/citiesActions';
import { connect } from 'react-redux';
const mapDispatchToProps = (dispatch) => ({
  dispatchAddCity: (city) => dispatch(addCity(city)),
  dispatchUpdateAsyncStorage: () => dispatch(updateAsyncStorage()),
});
const tabAddCityConnected =  connect(null, mapDispatchToProps)(tabAddCity)

const TabConfig = {
  CitiesTab: {
    screen: CitiesTab,
    navigationOptions: {
      tabBarLabel: 'Cities',
      tabBarIcon: ({ tintColor }) => (
        <Image
          source={require('./assets/cityicon.png')}
          style={[styles.icon, {tintColor: tintColor}]}
        />
      )
    }
  },
  AddCityTab: {
    // screen: AddCityTab,
    screen: tabAddCityConnected,
    navigationOptions: {
      tabBarLabel: 'Add City',
      tabBarIcon: ({ tintColor }) => (
        <Image
          source={require('./assets/addicon.png')}
          style={[styles.icon, {tintColor: tintColor}]}
        />
      )
    }
  }
}

const TabStyleConfig = {
  tabBarPosition: 'bottom',
  tabBarOptions: {
    activeTintColor: '#9C27B0',
    inactiveTintColor: '#666',
    showIcon: true,
    indicatorStyle: {
      backgroundColor: '#666'
    },
    style: {
      backgroundColor: '#ffffff',
      borderTopWidth: 1,
      borderTopColor: '#ededed'
    },
  },
}

export default App = TabNavigator(TabConfig, TabStyleConfig);

const styles = StyleSheet.create({
  icon: {
    width: 28,
    height: 28
  }
})
