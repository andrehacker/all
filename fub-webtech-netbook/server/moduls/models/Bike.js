module.exports = function(sequelize, DataTypes){
	return sequelize.define("Bike",{
		id: { type: Sequelize.INTEGER, autoIncrement: true },
		type:  {type: Sequelize.INTEGER},
		name: { type: Sequelize.STRING, allowNull: false},
		description: { type: Sequelize.TEXT, allowNull: false},
		img_url: { type: Sequelize.TEXT, allowNull: false},
		postion_lad: { type: Sequelize.STRING, allowNull: false},
		postion_long: { type: Sequelize.STRING, allowNull: false},
		deleted: {type: Sequelize.BOOLEAN, allowNull: false, defaultValue: false}
	})
}

